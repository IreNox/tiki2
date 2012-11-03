#include "Game/TikiBot.h"

#include "Core/LibraryManager.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"

#include "Game/GoalThink.h"

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
			controller->SetHeight(1.0f);
			controller->SetSlopeLimit(45.0f);
			controller->SetStepOffset(0.5f);
			controller->SetGroup(CG_Collidable_Pushable);
			controller->AddRef();

			// Create the goal queue
			brain = new GoalThink(this);
			//brain->RemoveAllSubgoals();
			// we must always have a goal in our brain
			brain->AddGoalWander();
			//brain->AddGoalSeek(Vector2(50, 50));


			// Navigation
            pathPlanner = new PathPlanner(this);
		}

		TikiBot::~TikiBot()
		{
			SafeRelease(&controller);
			
			SafeDelete(&brain);
			SafeDelete(&steering);
			SafeDelete(&pathPlanner);
		}

		bool TikiBot::IsAtPosition(Vector2 pos)
		{
			const static float tolerance = 2.0f;
			return Vector2::DistanceSquared(Pos(), pos) < tolerance;
		}

		void TikiBot::CreateNav(NavigationMesh* par, NavigationCell* currCell)
		{

            pathPlanner->Create(par);
		}


		void TikiBot::GotoLocation(const Vector3& p)
		{
            if (!pathPlanner->RequestPathTo(p))
            {
                OutputDebugString(L"No path found, steering toward target. \n");
            }
		}


		void TikiBot::Draw(const DrawArgs& args)
		{
			// connect the waypoins to draw lines in green
			#if _DEBUG
			if (!gameState->DrawNavMesh) return;

            pathPlanner->Draw(args);

			brain->Draw(args);


			#endif
		}

		void TikiBot::Update(const UpdateArgs& args)
		{
			// process the currently active goal. Note this is required even if the bot
			// is under user control. This is because a goal is created whenever a user 
			// clicks on an area of the map that necessitates a path planning request.
			brain->Process();

			// Update navigation
			//UpdateNavigation(args);
            pathPlanner->Update(args);

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

				if (gameObject->GModel()) gameObject->GModel()->SetAnimationSpeed(Vector2::Normalize(velocity).Length());
			}
			else
			{
				if (gameObject->GModel()) gameObject->GModel()->SetAnimationSpeed(0);
			}

			//velocity[bufferState.UpdateIndex] = new value;

			// Update the current cell if collider moved and the path is not active
			//if (!pathActive)
			//{
			//	NavigationCell* NextCell;
			//	Vector3 endPos = Pos3D() + Vector3(velocity.X, 0, velocity.Y);
			//	parent->ResolveMotionOnMesh(Pos3D(), currentCell, endPos, &NextCell);
			//	currentCell = NextCell;
			//}
		}

	}
}
