#pragma once


#include "Game/Regulator.h"
#include "Game/GameState.h"
#include "Game/TikiBot.h"

#include "Core/GameObject.h"
#include "Core/sqlite3.h"
#include "Core/TikiTimer.h"

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

			inline double GSpawnInterval() { return timerSpawn.Interval; }
			inline void SSpawnInterval(double interval) { timerSpawn.Interval = interval; }

			inline UInt32 GEnemySpawnCount() { return enemySpawnCount; }
			inline void SEnemySpawnCount(UInt32 count) { enemySpawnCount = count; }

			inline UInt32 GPlayerSpawnCount() { return playerSpawnCount; }
			inline void SPlayerSpawnCount(UInt32 count) { playerSpawnCount = count; }

			void CreateEnemy1(GameObject* go);
			//void CreateEnemy2(GameObject* go);
			void CreateEnemyTower(GameObject* go);
			void CreateEnemyBuilding(GameObject* go);
			
			void CreatePlayerMop(GameObject* go, const Vector3& destination);
			void CreatePlayerHero(GameObject* go);
			void CreatePlayerTower(GameObject* go);
			void CreatePlayerBuilding(GameObject* go);
			void CreatePlayerSpiderMine(GameObject* go, TikiBot* target);
			
			void CreateBuildSlot(GameObject* go);
			
			void Update(const UpdateArgs& args);

			Vector3 GetPos(const Vector2& pos, float heightAdjust);
			Vector3 GetPos(const Vector3& pos, float heightAdjust);

		private:

			GameState* gameState;

			Vector2 playerBase;
			std::list<Vector2> wayPoints;
			List<Vector3> spawnPoints;

			TikiTimer timerSpawn;
			TikiTimer timerNextUnit;

			UInt32 enemySpawnLeft;
			UInt32 enemySpawnCount;
			UInt32 playerSpawnLeft;
			UInt32 playerSpawnCount;

			void loadFromDatabase(sqlite3_stmt* state, GameObject* obj);

		};


	}
}