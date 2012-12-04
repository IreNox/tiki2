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

			inline double GSpawnInterval() { return interval; }
			inline void SSpawnInterval(double interval) { this->interval = interval; }

			inline UInt32 GEnemySpawnCount() { return enemySpawnCount; }
			inline void SEnemySpawnCount(UInt32 count) { enemySpawnCount = count; }

			inline UInt32 GPlayerSpawnCount() { return playerSpawnCount; }
			inline void SPlayerSpawnCount(UInt32 count) { playerSpawnCount = count; }

			void CreateEnemy1(GameObject* go);
			//void CreateEnemy2(GameObject* go);
			void CreateEnemyTower(GameObject* go);

			void CreatePlayerMop(GameObject* go);
			void CreatePlayerHero(GameObject* go);
			void CreatePlayerTower(GameObject* go);



			void Update(const UpdateArgs& args);

		private:

			GameState* gameState;

			Vector2 playerBase;
			std::list<Vector2> wayPoints;
			List<Vector3> spawnPoints;

			double interval;
			double elapsed;

			UInt32 enemySpawnCount;
			UInt32 playerSpawnCount;

			Vector3 getPos(const Vector2& pos);
			Vector3 getPos(const Vector3& pos);

		};


	}
}