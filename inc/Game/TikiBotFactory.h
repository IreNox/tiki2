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
			Vector3 spawnPoint1;
			Vector3 spawnPoint2;
			Vector3 spawnPoint3;

			double interval;
			double elapsed;
		};


	}
}