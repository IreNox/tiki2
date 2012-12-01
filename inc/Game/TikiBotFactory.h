#pragma once

#include "Game/Regulator.h"
#include "Core/GameObject.h"
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{

		class TikiBotFactory
		{
		public:

			TikiBotFactory(GameState* gameState);
			~TikiBotFactory();

			void Init();

			void SetSpawnInterval(double interval);

			void CreateEnemy1(GameObject* go);
			//void CreateEnemy2(GameObject* go);

			void CreatePlayerMop(GameObject* go);
			//void CreateHero(GameObject* go);
			//void CreateTower(GameObject* go);



			void Update(const UpdateArgs& args);

		private:
			//Regulator* spawnRegulator;
			GameState* gameState;

			std::list<Vector2> wayPoints;
			List<Vector3> spawnPoints;

			double interval;
			double elapsed;
		};


	}
}