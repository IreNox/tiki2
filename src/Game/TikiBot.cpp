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

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Components;

		TikiBot::TikiBot(GameState* gameState, GameObject* gameObject, TikiBotDescription desc) 
			: MovingEntity(gameState, gameObject)
		{
            // Init MovingEntity stats
            MovingEntity::Init(desc.Radius, Vector2::Zero, desc.MaxSpeed, desc.Heading, desc.MaxTurnRate, desc.MaxForce);


            // Init bot attributes
            faction = desc.Faction;

            maxHealth = desc.MaxHealth;
            health = maxHealth;

            numUpdatesHitPersistant = 12; //(int) (60 * 0.2);
            hit = false;
            score = 0;
            status = alive; //spawning;
            //possessed = true;
            fieldOfView = DegsToRads(desc.FoV);

            // TODO: game types
            //SetEntityType(type_bot);

            // create the navigation module
            pathPlanner = new PathPlanner(this);

            // Create steering behavior
            steering = new TikiSteering(this);

            // init CharacterController
            controller = engine->librarys->CreateComponent<ICharacterController>(gameObject);
            controller->SetCenter(Pos3D());
            controller->SetRadius((float)boundingRadius);
            controller->SetHeight(desc.Height);
            controller->SetSlopeLimit(desc.SlopeLimit);
            controller->SetStepOffset(desc.StepOffset);
            controller->SetGroup(CG_Collidable_Pushable);
            controller->AddRef();

            // create regulators
            visionUpdateRegulator = new Regulator(4.0);
            targetSelectionRegulator = new Regulator(2.0);



            // create Targeting System
            targSys = new TargetingSystem(this);

            // we can remember bots
            sensorMem = new SensorMemory(this, desc.MemorySpan);

            weaponSys = new WeaponSystem(this);
            weaponSys->Init(desc.ReactionTime, desc.AimAccuracy, desc.AimPresistance);

            // Create the goal queue
            brain = new GoalThink(this);
            brain->Init(desc.ExploreBias, desc.AttackBias, desc.PatrolBias);

		}

		TikiBot::~TikiBot()
		{
			SafeRelease(&controller);
			
			SafeDelete(&brain);
			SafeDelete(&steering);
			SafeDelete(&pathPlanner);
			SafeDelete(&sensorMem);
			SafeDelete(&targSys);
			SafeDelete(&visionUpdateRegulator);
			SafeDelete(&targetSelectionRegulator);

		}

// 		void TikiBot::Init(TikiBotDescription desc)
// 		{
// 
// 
// 		}

		void TikiBot::CreateNav(NavigationMesh* par, NavigationCell* currCell)
		{
            pathPlanner->Create(par);
		}

		void TikiBot::ReduceHealth(unsigned int val)
		{
			health -= val;

			if (health <= 0)
				SetDead();

			hit = true;

			const int FrameRate = 60;
			const float HitFlashTime = 0.2f;
			numUpdatesHitPersistant = (int)(FrameRate * HitFlashTime);
		}

		void TikiBot::IncreaseHealth(unsigned int val)
		{
			health += val; 
			ClampT(health, 0, maxHealth);
		}


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
			return ( Vector2::DistanceSquared(Pos(), pos) < 5.0f);
		}

		bool TikiBot::HasLOSTo(Vector3 pos)
		{
			bool los = false;

			Ray ray(Vector3::Zero, Vector3::Zero);

			// Move y Up, else we raycast against the bot's own collider.
			float headingEps = 0.5f;
			ray.Origin = Pos3D();
			ray.Origin.Y += controller->GetHeight() * 0.5f + controller->GetRadius();
            
            //ray.Origin = Pos3D() + (Vector3::Normalize(Vector3(heading.X, 0, heading.Y)) * (controller->GetRadius() + headingEps));
			ray.Direction = pos - ray.Origin;

			orig = ray.Origin;
			dir = ray.Direction;

			RaycastHit info;

			if (engine->physics->RayCast(ray, &info, weaponSys->GetCurrentWeapon()->GetIdealRange()))
			{				
				float eps = 5.0f;
				// check the intersection points for nearly equal
				if (info.Point.X >= pos.X - eps && info.Point.X <= pos.X + eps &&
					info.Point.Y >= pos.Y - eps && info.Point.Y <= pos.Y + eps &&
					info.Point.Z >= pos.Z - eps && info.Point.Z <= pos.Z + eps)
					los = true;
			}

			return los;
		}

		void TikiBot::TakePossession()
		{
// 			// TODO: Player + enemy bots check
// 			if ( !(IsSpawning() || IsDead()) )
// 				possessed = true;
		}

		void TikiBot::Exorcise()
		{
			//possessed = false;
			//brain->AddGoalExplore();
		}

		void TikiBot::Draw(const DrawArgs& args)
		{
			// connect the waypoins to draw lines in green
			#if _DEBUG
			if (!gameState->DrawNavMesh) return;

            pathPlanner->Draw(args);

			brain->Draw(args);

			// draw raycast Check
			args.Graphics->DrawLine(orig, orig + dir, Color::Blue);

			// draw recently sensed opponents
			sensorMem->Draw(args);
			#endif
		}

		void TikiBot::Update(const UpdateArgs& args)
		{
			// process the currently active goal. Note this is required even if the bot
			// is under user control. This is because a goal is created whenever a user 
			// clicks on an area of the map that necessitates a path planning request.
			brain->Process(args);

			//Calculate the steering force and update the bot's velocity and position
			UpdateMovement(args);


			//examine all the opponents in the bots sensory memory and select one to be the current target
			//if (targetSelectionRegulator->IsReady())
				targSys->Update(args);

			// update the sensory memory with any visual stimulus
			//if (visionUpdateRegulator->IsReady())
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



				if (gameObject->GModel()) 
					gameObject->GModel()->SetAnimationSpeed(Vector2::Normalize(velocity).Length());
			}
			else
			{


				if (gameObject->GModel()) 
					gameObject->GModel()->SetAnimationSpeed(0);
			}

			// always update rotation
			gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(
				(3.14159f - atan2(heading.Y, heading.X)) - (3.14159f / 2), 0, 0
				);

			//velocity[bufferState.UpdateIndex] = new value;
		}

	}
}
