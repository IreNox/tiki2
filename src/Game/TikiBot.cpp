#include "Game/TikiBot.h"

#include "Core/LibraryManager.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"
#include "Core/IPhysics.h"
#include "Core/Ray.h"

#include "Game/GoalThink.h"
#include "Game/SensorMemory.h"
#include "Game/WeaponSystem.h"
#include "Game/Weapon.h"
#include "Game/SkillSystem.h"
#include "Game/TargetingSystem.h"
#include "Game/AttributeSystem.h"

#include "Game/SceneLevel.h"

#include "Game/GD.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Components;

		static GoalTypeToString* ttsInstance = new GoalTypeToString();

		#pragma region Class
		TikiBot::TikiBot(GameState* gameState, GameObject* gameObject, const TikiBotDescription& desc) 
			: MovingEntity(gameState, gameObject), attSys(gameObject->GetEngine())
		{
            // Init MovingEntity stats
            MovingEntity::Init(desc.Radius, Vector2::Zero, desc.MaxSpeed, desc.Heading, desc.MaxTurnRate, desc.MaxForce);

            // Init bot attributes
            faction = desc.Faction;
			sightRadius = desc.SightRadius;
			loot = desc.Loot;
			armor = desc.Armor;
			type = desc.EntityType;

			attSys[TA_MaxHealth] = desc.MaxHealth;
            //maxHealth = desc.MaxHealth;
            health = attSys[TA_MaxHealth];

            numUpdatesHitPersistant = 12; //(int) (60 * 0.2);
            hit = false;
            status = alive;
            fieldOfView = DegsToRads(desc.FoV);

            // create the navigation module
            pathPlanner = new PathPlanner(this);

            // Create steering behavior
            steering = new TikiSteering(this);

            // init CharacterController
            controller = engine->librarys->CreateComponent<ICharacterController>(gameObject);
            controller->SetCenter(Pos3D() + Vector3(0, desc.Height / 2, 0));
            controller->SetRadius((float)boundingRadius);
            controller->SetHeight(desc.Height);
            controller->SetSlopeLimit(desc.SlopeLimit);
            controller->SetStepOffset(desc.StepOffset);
            controller->SetGroup(CG_Collidable_Pushable);
            controller->AddRef();

            // create regulators
            visionUpdateRegulator = new Regulator(12.0);
            targetSelectionRegulator = new Regulator(12.0);

			if (type != ET_Building)
			{
				// create Targeting System
				targSys = new TargetingSystem(this);

				// we can remember bots
				sensorMem = new SensorMemory(this, desc.MemorySpan);

				weaponSys = new WeaponSystem(this);
				weaponSys->Init(desc);

				skillSys = new SkillSystem(this);

				// Create the goal queue
				brain = new GoalThink(this);
				brain->Init(desc.ExploreBias, desc.AttackBias, desc.PatrolBias);
			}
			else
			{
				targSys = 0;
				sensorMem = 0;
				weaponSys = 0;
				brain = 0;
				skillSys = 0;
			}

			pathPlanner->Create(
				gameState->GetNavMesh()
			);			
		}

		TikiBot::~TikiBot()
		{
			SafeRelease(&controller);
			
			SafeDelete(&brain);
			SafeDelete(&skillSys);
			SafeDelete(&steering);
			SafeDelete(&pathPlanner);
			SafeDelete(&sensorMem);
			SafeDelete(&targSys);
			SafeDelete(&weaponSys);
			SafeDelete(&visionUpdateRegulator);
			SafeDelete(&targetSelectionRegulator);

		}
		#pragma endregion

		#pragma region Member - Health
		void TikiBot::ReduceHealth(double val)
		{
			health -= val;

			if (health <= 0)
			{
				OnDeath.RaiseEvent(this, BotDeadArgs(this));
				SetDead();
			}
			hit = true;

			const int FrameRate = 60;
			const float HitFlashTime = 0.2f;
			numUpdatesHitPersistant = (int)(FrameRate * HitFlashTime);
		}

		void TikiBot::IncreaseHealth(double val)
		{
			health += val; 
			ClampT(health, 0.0f, attSys[TA_MaxHealth]);
		}
		#pragma endregion
		
		#pragma region Member - Killed Bot
		void TikiBot::KilledBot(TikiBot* deadBot)
		{
			if (this->EntityType() == ET_Hero && deadBot->GetFaction() != faction)
			{
				switch (deadBot->EntityType())
				{
					case ET_Bot:
						skillSys->IncementXP(XPKillBot);
						gameState->IncrementResource(ResKillBot);
						break;
					case ET_Tower:
						skillSys->IncementXP(XPKillTower);
						gameState->IncrementResource(ResKillTower);
						break;
					case ET_Building:
						skillSys->IncementXP(XPKillBuilding);
						gameState->IncrementResource(ResKillBuilding);
						break;
				}
			}
		}
		#pragma endregion

		#pragma region Member - Misc
		bool TikiBot::RotateFacingTowardPosition(Vector2 target)
		{
			Vector2 toTarget = Vector2::Normalize(target - Pos());

			float dot = Vector2::Dot(heading, toTarget);
			
			// clamp to rectify any rounding errors
			ClampT(dot, -1, 1);

			//determine the angle between the heading vector and the target
			float angle = acosf(dot);

			// return true if the bot's facing is within WeaponAimTolerance degs of facing the target
			if (angle < 0.01f) 
			{
				heading = toTarget;
				return true;
			}
			// clamp the amount to turn to the max turn rate
			if (angle > (float)maxTurnRate)
				angle = (float)maxTurnRate;

			// use a rotation matrix to rotate the player's facing vector accordingly
			// the direction of rotation has to be determined when creating the rotation matrix
			Matrix3x3 rotMatrix = rotMatrix.Rotate(angle * heading.Sign(toTarget));
            heading = rotMatrix.TransformVector(heading);
            velocity = rotMatrix.TransformVector(velocity);

            side = heading.Cross();
			return false;
		}
		
		bool TikiBot::IsAtPosition(Vector2 pos)
		{
			return ( Vector2::DistanceSquared(Pos(), pos) < 2.0f);
		}

		bool TikiBot::HasLOSTo(Vector3 pos, float dist, float eps)
		{
			bool los = false;

			Ray ray(Vector3::Zero, Vector3::Zero);
			ray.Origin = Pos3D() + (Vector3::Normalize(pos - Pos3D()) * controller->GetRadius() * 2.0f);
			//ray.Origin.Y += (controller->GetHeight() * 0.6f) + (controller->GetRadius() + 1.0f);
			//ray.Origin = Pos3D() + (dir * controller->GetRadius() * 2.0f);
			//ray.Origin.Y += controller->GetHeight() * 2.1f; // * 0.6f + controller->GetRadius();
            
			ray.Direction = pos - ray.Origin;
			//ray.Origin = Pos3D() + (Vector3::Normalize(Vector3(heading.X, 0, heading.Y)) * (controller->GetRadius() + headingEps));
			//ray.Origin = Pos3D() + (Vector3::Normalize(ray.Direction) * controller->GetRadius() * 1.1f);

			orig = ray.Origin;
			dir = ray.Direction;

			RaycastHit info;

			if (engine->physics->RayCast(ray, &info, dist))
			{				
#if _DEBUG
				if (info.Collider == controller)
				{
					//_CrtDbgBreak();
					// RayCast ist falsch und trifft sich selbst
				}
#endif
				// check the intersection points for nearly equal
				if (info.Point.X >= pos.X - eps && info.Point.X <= pos.X + eps &&
					info.Point.Y >= pos.Y - eps && info.Point.Y <= pos.Y + eps &&
					info.Point.Z >= pos.Z - eps && info.Point.Z <= pos.Z + eps)
					los = true;
			}

			return los;
		}

//		void TikiBot::TakePossession()
//		{
//// 			// TODO: Player + enemy bots check
//// 			if ( !(IsSpawning() || IsDead()) )
//// 				possessed = true;
//		}
//
//		void TikiBot::Exorcise()
//		{
//			//possessed = false;
//			//brain->AddGoalExplore();
//		}

		void TikiBot::Teleport(const Vector3& pos)
		{
			Vector3 sp = pos;
			sp.Y += controller->GetHeight();

			controller->SetCenter(sp);
		}
		#pragma endregion

		#pragma region Member - Draw
		void TikiBot::Draw(const DrawArgs& args)
		{		
			// Draw Hero Skills
			if (EntityType() == ET_Hero)
				skillSys->Draw(args);
			
			// connect the waypoins to draw lines in green
			#if _DEBUG
			if (gameState->DrawNavMesh && EntityType() != ET_Building)
			{
				Matrix vp = args.CurrentCamera->WorldToScreen();

				pathPlanner->Draw(args);
				brain->Draw(args);

				// draw raycast Check
				args.Graphics->DrawLine(orig, orig + dir, Color::Blue);

				// draw recently sensed opponents
				sensorMem->Draw(args);

				// Draw Goals
				Camera* cam = gameState->GetScene()->GetMainCamera();
				Vector2 bbDim = engine->graphics->GetViewPort()->GetSize();

				Vector3 screenPos = Matrix::Project(Pos3D(), 0, 0, bbDim.X, bbDim.Y, -1, 1, vp);

				brain->DrawAtPos(args, Vector2(screenPos.X, screenPos.Y), ttsInstance);
			}
			#endif
		}
		#pragma endregion

		#pragma region Member - Update
		void TikiBot::Update(const UpdateArgs& args)
		{
			// don't do this for buildings
			if (EntityType() == ET_Building)
				return;

			// Update Hero Skills
			if (EntityType() == ET_Hero)
				skillSys->Update(args);
			
			if (EntityType() == ET_Tower)
			{
				Quaternion rot = gameObject->PRS.GRotation();

				if (rot != Quaternion::Identity)
				{
					gameObject->GModel()->GetMesh("tower")->SetLocalMatrix(Matrix::CreateFromQuaternion(rot));
					gameObject->PRS.SRotation() = Quaternion::Identity;
				}
			}

			double addHealth = attSys[TA_HealthRegValue] * args.Time.ElapsedTime;
			addHealth += attSys[TA_HealthRegPercent] * attSys[TA_MaxHealth] * 0.01 * args.Time.ElapsedTime;

			if (addHealth != 0.0)
				this->IncreaseHealth(addHealth);

			// process the currently active goal. Note this is required even if the bot
			// is under user control. This is because a goal is created whenever a user 
			// clicks on an area of the map that necessitates a path planning request.
			brain->Process(args);

			//Calculate the steering force and update the bot's velocity and position
			UpdateMovement(args);


			//examine all the opponents in the bots sensory memory and select one to be the current target
			if (targetSelectionRegulator->IsReady())
				targSys->Update(args);

			// update the sensory memory with any visual stimulus
			if (visionUpdateRegulator->IsReady())
				sensorMem->UpdateVision(args);
		
			
            // aim the current weapon at the current target and takes a shot if possible
            weaponSys->TakeAimAndShoot(args);
		}


		void TikiBot::UpdateMovement(const UpdateArgs& args)
		{
			// calculate the combined steering force
			Vector2 force = steering->Calculate();

			// if no steering force is produced decelerate the player by applying a braking force
			if (steering->Force().IsZero())
			{
				const float BrakingRate = 0.8f;
				velocity = velocity * BrakingRate;
			}

			//calculate the acceleration
			Vector2 accel = force / (float)mass;

			//update the velocity
			velocity += accel;

			//make sure vehicle does not exceed maximum velocity
			velocity.Truncate((float)maxSpeed);

			// Move the controller and set some gravity
			Vector3 displacement(velocity.X,
								 -9.81f, 
								 velocity.Y); 
			controller->Move(displacement * (float)args.Time.ElapsedTime);



			//if the vehicle has a non zero velocity the heading and side vectors must be updated
			if (!velocity.IsZero())
			{    
				heading = Vector2::Normalize(velocity);
				side = heading.Cross();

				//TODO MATCH WALKING SPEED

				//if (gameObject->GModel()) 
				//	gameObject->GModel()->SetAnimationSpeed(Vector2::Normalize(velocity).Length());
			}
			else
			{


				//if (gameObject->GModel()) 
				//	gameObject->GModel()->SetAnimationSpeed(0);
			}

			// always update rotation
			gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(
				(3.14159f - atan2(heading.Y, heading.X)) - (3.14159f / 2), 0, 0
				);

			//velocity[bufferState.UpdateIndex] = new value;
		}
		#pragma endregion
	}
}
