#include "Game/TikiBot.h"
#include "Core/LibraryManager.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Components;

		TikiBot::TikiBot(Engine* engine, GameObject* gameObject) 
			: MovingEntity(engine, gameObject)
		{

			// Init MovingEntity stats
			Init();

			// Init bot stats
			maxHealth = 100;
			health = maxHealth;

			numUpdatesHitPersistant = 12; //(int) (60 * 0.2);
			hit = false;
			score = 0;
			status = spawning;
			possessed = false;
			fieldOfView = DegsToRads(180);

			// TODO: game types
			//SetEntityType(type_bot);

			// a bot starts off facing in the direction it is heading
			facing = heading;

			steering = new TikiSteering(this);



			// init CharacterController
			controller = engine->librarys->CreateComponent<ICharacterController>(gameObject);
			controller->SetCenter(Vector3(Pos().X, 5, Pos().Y));
			controller->SetRadius((float)boundingRadius);
			controller->SetHeight(1.0f);
			controller->SetSlopeLimit(45.0f);
			controller->SetStepOffset(0.5f);
			controller->SetGroup(CG_Collidable_Non_Pushable);

		}

		TikiBot::~TikiBot()
		{
			SafeRelease(&controller);
			delete steering;
		}

		void TikiBot::Draw(const DrawArgs& args)
		{
		}

		void TikiBot::Update(const UpdateArgs& args)
		{

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
			Vector3 displacement(velocity.X, -9.81f, velocity.Y); 
			controller->Move(displacement * (float)args.Time.ElapsedTime);

			//if the vehicle has a non zero velocity the heading and side vectors must be updated
			if (!velocity.IsZero())
			{    
				heading = Vector2::Normalize(velocity);

				side = heading.Cross();
			}

		}


	}
}