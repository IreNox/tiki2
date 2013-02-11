#pragma once


#include "Game/Regulator.h"
#include "Game/GameState.h"
#include "Game/TikiBot.h"

#include "Core/GameObject.h"
#include "Core/TikiTimer.h"

#include "Game/PlayerBase.h"
#include "Game/EnemyBase.h"
#include "Game/TikiAtt.h"
#include "Game/EventHeroEvents.h"

namespace TikiEngine
{
	namespace Game
	{
		class TikiBotFactory : public HeroLevelUpEventHandler
		{
		public:

			TikiBotFactory(GameState* gameState);
			~TikiBotFactory();

			void Init();

			void CreateEnemy1(GameObject* go, const List<Vector2>& wayPoints);
			//void CreateEnemy2(GameObject* go);
			void CreateEnemyTower(GameObject* go);
			void CreateEnemyBuilding(GameObject* go);
			
			void CreatePlayerMop(GameObject* go, const Vector3& destination);
			void CreatePlayerHero(GameObject* go);
			void CreatePlayerSpiderMine(GameObject* go, const Vector3& target);

			void CreatePlayerTower(GameObject* go);
			void CreatePlayerMainBuilding(GameObject* go);
			void CreatePlayerHeroPlatform(GameObject* go);
			void CreatePlayerSpawnBuilding(GameObject* go);
			
			void CreateBuildSlot(GameObject* go);
			
			void Update(const UpdateArgs& args);

			Vector3 GetPos(const Vector2& pos, float heightAdjust);
			Vector3 GetPos(const Vector3& pos, float heightAdjust);
			
			void Handle(TikiBot* sender, const HeroLevelUpEventArgs& args);

		private:

			GameState* gameState;

			UInt32 gameTime;
			TikiTimer timerSpawn;
			TikiTimer timerNextUnit;

			UInt32 enemySpawnLeft;
			UInt32 playerSpawnLeft;

			PlayerBase* playerBase;
			List<EnemyBase*> enemyBases;

			TikiAttModifier amodBuildingLifeReg;

			TikiAttModifier amodHeroArmor;
			TikiAttModifier amodHeroDamage;
			TikiAttModifier amodHeroLifeReg;
			TikiAttModifier amodHeroAttackSpeed;

			void loadFromDatabase(sqlite3_stmt* state, GameObject* obj);

		};


	}
}