#include "Game/TikiBot.h"


namespace TikiEngine
{
	namespace AI
	{

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

			//create the steering behavior class


		}

		TikiBot::~TikiBot()
		{
			//delete steering;
		}

		void TikiBot::Draw(const DrawArgs& args)
		{
		}

		void TikiBot::Update(const UpdateArgs& args)
		{

			//Calculate the steering force and update the bot's velocity and position
			UpdateMovement();

		}


		void TikiBot::UpdateMovement()
		{

		}


	}
}