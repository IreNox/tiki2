#include "Game/TikiBotFactory.h"

#include "Game/TikiBot.h"
#include "Game/GoalThink.h"
#include "Game/AnimationHandlerDefaultUnit.h"
#include "Game/SceneLevel.h"
#include "Game/BuildSlot.h"

#include "Core/IContentManager.h"


namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		TikiBotFactory::TikiBotFactory(GameState* gameState)
			: gameState(gameState), elapsed(0), interval(30000000.0), enemySpawnCount(7), playerSpawnCount(5)
		{
		}

		TikiBotFactory::~TikiBotFactory()
		{
		}
		#pragma endregion

		#pragma region Member - Init
		void TikiBotFactory::Init()
		{
			const List<LevelPoint*>& points = gameState->GetScene()->GPoints();

			UInt32 i = 0;
			while (i < points.Count())
			{
				switch (points[i]->GType())
				{
				case 1:
					playerBase = points[i]->GPosition();
					break;
				case 2:
					wayPoints.push_back(points[i]->GPosition());
					break;
				case 3:
					spawnPoints.Add(getPos(points[i]->GPosition()));
					break;
				}

				i++;
			}		
		}
		#pragma endregion

		#pragma region Member - Update
		void TikiBotFactory::Update( const UpdateArgs& args )
		{
			elapsed += args.Time.ElapsedTime;

			if (elapsed > interval)
			{
				elapsed -= interval;

				// spawn from three sides
				UInt32 i = 0;
				while (i < spawnPoints.Count())
				{
					UInt32 a = 0;
					while (a < enemySpawnCount)
					{
						GameObject* go = new GameObject(gameState->GetEngine());
						go->PRS.SPosition() = getPos(spawnPoints[i]);
						CreateEnemy1(go);

						a++;
					}

					i++;
				}

				UInt32 a = 0;
				while (a < playerSpawnCount)
				{
					GameObject* go = new GameObject(gameState->GetEngine());
					go->PRS.SPosition() = getPos(spawnPoints[i]);
					CreatePlayerMop(go);

					a++;
				}
			}

#if _DEBUG
			if (args.Input.GetKeyPressed(KEY_F5))
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = getPos(spawnPoints[0]);
				CreateEnemy1(go);
			}

			//if (args.Input.GetKeyPressed(KEY_F6))
			//{
			//	GameObject* go = new GameObject(gameState->GetEngine());
			//	go->PRS.SPosition() = getPos(Vector2(100, 100));
			//	CreateEnemyTower(go);
			//}

			if (args.Input.GetKeyPressed(KEY_F7))
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = getPos(Vector2(10, 10));
				CreatePlayerHero(go);
			}


			if (args.Input.GetKeyPressed(KEY_F8))
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->PRS.SPosition() = getPos(Vector2(10, 10));
				CreatePlayerMop(go);
			}

#endif
		}
		#pragma endregion

		#pragma region Member - Create - Enemy
		void TikiBotFactory::CreateEnemy1(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"soldier"));
			go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.Height = 9.0f;
			botDesc.Radius = 3.5f;
			botDesc.MaxHealth = 30;			
			botDesc.entityType = ET_Bot;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.06f);
			bot->CreateNav(gameState->GetNavMesh());

			if (!wayPoints.empty())
			{
				bot->GetBrain()->AddGoalPatrol(wayPoints);
			}

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreateEnemyTower(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"replaceme_cube"));
			//go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.Height = 9.0f;
			botDesc.Radius = 3.5f;
			botDesc.MaxHealth = 100;	
			botDesc.MaxSpeed = 0.000001f;
			botDesc.entityType = ET_Tower;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(8.0f);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->GetBrain()->AddGoalExplore();

			gameState->GetScene()->AddElement(go);
		}


		void TikiBotFactory::CreateEnemyBuilding( GameObject* go )
		{
			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.Height = 5.0f;
			botDesc.Radius = 5.0f;
			botDesc.MaxHealth = 100;	
			botDesc.MaxSpeed = 0.000001f;
			botDesc.entityType = ET_Building;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);

			gameState->GetScene()->AddElement(go);
		}

		#pragma endregion

		#pragma region Member - Create - Player
		void TikiBotFactory::CreatePlayerHero(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"marine_l"));
			go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 11.0f;
			botDesc.Radius = 3.5f;
			botDesc.MaxHealth = 300;
			botDesc.entityType = ET_Hero;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.1f);
			bot->CreateNav(gameState->GetNavMesh());

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerMop(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"marine_l"));
			go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 8.0f;
			botDesc.Radius = 4.0f;
			botDesc.MaxHealth = 30;
			botDesc.entityType = ET_Bot;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.06f);
			bot->CreateNav(gameState->GetNavMesh());

			bot->GetBrain()->AddGoalAttackMove(spawnPoints[0]);

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerTower(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"replaceme_cube"));
			//go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 9.0f;
			botDesc.Radius = 3.5f;
			botDesc.MaxHealth = 100;	
			botDesc.MaxSpeed = 0.000001f;
			botDesc.entityType = ET_Tower;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(8.0f);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->GetBrain()->AddGoalExplore();


			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerBuilding(GameObject* go)
		{
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 5.0f;
			botDesc.Radius = 5.0f;
			botDesc.MaxHealth = 100;	
			botDesc.MaxSpeed = 0.000001f;
			botDesc.entityType = ET_Building;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);

			gameState->GetScene()->AddElement(go);
		}
		#pragma endregion

		#pragma region Member - Create - BuildSlot
		void TikiBotFactory::CreateBuildSlot(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"replaceme_cube"));

			BuildSlot* slot = new BuildSlot(gameState, go);
			//slot->GetGameObject()->PRS.SScale() = Vector3(8.0f, 8.0f, 8.0f);
			gameState->GetScene()->AddElement(go);
		}
		#pragma endregion

		#pragma region Private Member
		Vector3 TikiBotFactory::getPos(const Vector2& pos)
		{
			Vector3 outPos;
			
			outPos.X = pos.X + Random(3, 10);
			outPos.Z = pos.Y + Random(3, 10);

			outPos.Y = gameState->GetScene()->GLevel()->GetTerrain()->SampleHeight(outPos) + 10.0f;
			return outPos;
		}

		Vector3 TikiBotFactory::getPos(const Vector3& pos)
		{
			return getPos(Vector2(pos.X, pos.Z));
		}

		#pragma endregion

		#pragma region Private Member - Database
		void TikiBotFactory::loadFromDatabase(sqlite3_stmt* state, GameObject* obj)
		{
			TikiBotDescription desc;

			//desc.MaxHealth = sqlite3_column_int(state, fieldId);
			//desc.HealthReg = sqlite3_column_int(state, fieldId);
			//desc.Sichtweite = sqlite3_column_int(state, fieldId);
			//desc.Loot = sqlite3_column_int(state, fieldId);
			//desc.Armor = sqlite3_column_int(state, fieldId);
			//desc.weapon = load weapon from database;
			
			//TikiBot* bot = createBot(desc);
			//bot->GetWeaponSys()->SetWeapon(from weapon id);

			/////////////////////////////////////////////////////////////////////////////////

			//obj->SModel(***);

			//foreach (AttributesModificator am in Db.GetAttributes())
			//{
				//bot->GetAttributes()->add(am);
			//}
		}
		#pragma endregion
	}
}
