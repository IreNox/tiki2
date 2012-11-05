#include "Game/TikiBot.h"

#include "Core/LibraryManager.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"
#include "Core/IPhysics.h"
#include "Core/Ray.h"

#include "Game/GoalThink.h"
#include "Game/SensorMemory.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Components;

		TikiBot::TikiBot(GameState* gameState, GameObject* gameObject) 
			: MovingEntity(gameState, gameObject)
		{

			// Init MovingEntity stats
			Init();

			// Init bot attributes
			maxHealth = 100;
			health = maxHealth;

			numUpdatesHitPersistant = 12; //(int) (60 * 0.2);
			hit = false;
			score = 0;
			status = alive; //spawning;
			possessed = false;
			fieldOfView = DegsToRads(180);

			// TODO: game types
			//SetEntityType(type_bot);

			// a bot starts off facing in the direction it is heading
			facing = heading;

			// Create steering behavior
			steering = new TikiSteering(this);

			// init CharacterController
			controller = engine->librarys->CreateComponent<ICharacterController>(gameObject);
			controller->SetCenter(Pos3D());
			controller->SetRadius((float)boundingRadius);
			controller->SetHeight(3.0f);
			controller->SetSlopeLimit(45.0f);
			controller->SetStepOffset(0.5f);
			controller->SetGroup(CG_Collidable_Pushable);
			controller->AddRef();

			// Create the goal queue
			brain = new GoalThink(this);

			// Navigation
            pathPlanner = new PathPlanner(this);

			sensorMem = new SensorMemory(this, 5);

			
		}

		TikiBot::~TikiBot()
		{
			SafeRelease(&controller);
			
			SafeDelete(&brain);
			SafeDelete(&steering);
			SafeDelete(&pathPlanner);
			SafeDelete(&sensorMem);
		}

		void TikiBot::CreateNav(NavigationMesh* par, NavigationCell* currCell)
		{
            pathPlanner->Create(par);
		}

		bool TikiBot::IsAtPosition(Vector2 pos)
		{
			return ( Vector2::DistanceSquared(Pos(), pos) < 0.1f);
		}

		bool TikiBot::HasLOSTo(Vector3 pos)
		{
			bool los = false;

			Ray ray(Vector3::Zero, Vector3::Zero);

			// Move y Up, else we raycast against the bot's own collider.
			float heightEps = 1.0f;
			ray.Origin = Pos3D();
			ray.Origin.Y += controller->GetHeight() * 0.5f + controller->GetRadius();
			ray.Direction = pos - ray.Origin;

			orig = ray.Origin;
			dir = ray.Direction;

			RaycastHit info;

			if (engine->physics->RayCast(ray, &info))
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

		void TikiBot::Draw(const DrawArgs& args)
		{
			// connect the waypoins to draw lines in green
			#if _DEBUG
			if (!gameState->DrawNavMesh) return;

            pathPlanner->Draw(args);

			brain->Draw(args);

			// draw raycast Check
			args.Graphics->DrawLine(orig, orig + dir, Color::Blue);
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

				gameObject->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(
					(3.14159f - atan2(velocity.Y, velocity.X)) - (3.14159f / 2), 0, 0
				);

				if (gameObject->GModel()) 
					gameObject->GModel()->SetAnimationSpeed(Vector2::Normalize(velocity).Length());
			}
			else
			{
				if (gameObject->GModel()) 
					gameObject->GModel()->SetAnimationSpeed(0);
			}

			//velocity[bufferState.UpdateIndex] = new value;
		}

	}
}
