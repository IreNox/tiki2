#include "Game/TikiBotFactory.h"

#include "Game/TikiBot.h"
#include "Game/GoalThink.h"
#include "Game/AnimationHandlerDefaultUnit.h"
#include "Game/SceneLevel.h"
#include "Game/BuildSlot.h"

#include "Game/SkillRocket.h"
#include "Game/SkillFlash.h"
#include "Game/SkillHealAura.h"
#include "Game/SkillSpiderMine.h"
#include "Game/SkillSystem.h"

#include "Game/Trigger.h"
#include "Core/IContentManager.h"

#include "Game/GD.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		TikiBotFactory::TikiBotFactory(GameState* gameState)
			: gameState(gameState), timerSpawn(SPAWN_INTERVAL), timerNextUnit(SPAWN_UNIT_INTERVAL), enemySpawnLeft(0), playerSpawnLeft(0),
			  playerBase(0)
		{
			playerBase = gameState->GetPart<PlayerBase>(0);
		}

		TikiBotFactory::~TikiBotFactory()
		{
		}
		#pragma endregion

		#pragma region Member - Init
		void TikiBotFactory::Init()
		{
			playerBase->Init();
            playerBase->Hero->AddRef();

			enemyBases.Clear();
			gameState->GetParts<EnemyBase>(enemyBases);
			FOREACH_PTR_CALL(enemyBases, Init())
		}
		#pragma endregion

		#pragma region Member - Update
		void TikiBotFactory::Update(const UpdateArgs& args)
		{
			if (timerSpawn.IsReady(args.Time))
			{
				enemySpawnLeft += SPAWN_ENEMY_COUNT;
				playerSpawnLeft += SPAWN_PLAYER_COUNT;

				timerNextUnit.ResetToReady();
			}

			if ((enemySpawnLeft != 0 || playerSpawnLeft != 0) && timerNextUnit.IsReady(args.Time))
			{
				UInt32 i = 0;
				while (i < enemyBases.Count())
				{
					enemyBases[i]->Spawn(
						enemySpawnLeft > 0,
						playerSpawnLeft > 0,
						playerBase->SpawnPoint->GPosition()
					);

					i++;
				}

				if (enemySpawnLeft > 0) enemySpawnLeft--;
				if (playerSpawnLeft > 0) playerSpawnLeft--;
			}
		}
		#pragma endregion

		#pragma region Member - Create - Enemy
		void TikiBotFactory::CreateEnemy1(GameObject* go, const List<Vector2>& wayPoints)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"soldier"));
			go->GModel()->GetMesh("heavyPlasma")->SetVisible(false);
			
			auto ah = new AnimationHandlerDefaultUnit(go->GModel());
			go->GModel()->AnimationHandler.AddHandler(ah);
			go->SetUserData(ah);
			
			//go->GetSceneGraphElement().IsDynamic();


			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.Height = 2.0f;
			botDesc.Radius = 1.8f;
			botDesc.MaxHealth = 30;			
			botDesc.EntityType = ET_Bot;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);

			if (wayPoints.Count() != 0)
			{
				bot->GetBrain()->RemoveAllSubgoals();
				bot->GetBrain()->QueueGoalAttackMove(GetPos(wayPoints[0], 0.05f));
			}

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreateEnemyTower(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"tower_enemy"));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.Height = 5.0f;
			botDesc.Radius = 3.0f;
			botDesc.MaxHealth = 100;	
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Tower;

			go->PRS.SPosition() = GetPos(Vector2(go->PRS.GPosition().X, go->PRS.GPosition().Z), 4.0f);

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->GetBrain()->AddGoalExplore();

			gameState->GetScene()->AddElement(go);
		}


		void TikiBotFactory::CreateEnemyBuilding( GameObject* go )
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"building03_05"));

			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.Height = 8.0f;
			botDesc.Radius = 8.0f; //5.0f;
			botDesc.MaxHealth = 100;	
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Building;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->SetScale(1.0f);

			gameState->GetScene()->AddElement(go);
		}

		#pragma endregion

		#pragma region Member - Create - Player - Units
		void TikiBotFactory::CreatePlayerHero(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"marine_l"));
			go->GModel()->GetMesh("heavyPlasma")->SetVisible(false);

			auto ah = new AnimationHandlerDefaultUnit(go->GModel());
			go->GModel()->AnimationHandler.AddHandler(ah);
			go->SetUserData(ah);

#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 2.0f;
			botDesc.Radius = 1.8f;
			botDesc.MaxHealth = 300;
			botDesc.EntityType = ET_Hero;
			botDesc.MaxSpeed = 7.0f;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);

			bot->GetSkillSys()->AddSkill(new SkillFlash(bot));
			bot->GetSkillSys()->AddSkill(new SkillRocket(bot));
			bot->GetSkillSys()->AddSkill(new SkillHealAura(bot));
			bot->GetSkillSys()->AddSkill(new SkillSpiderMine(bot));

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerMop(GameObject* go, const Vector3& dest)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"marine_l"));
			go->GModel()->GetMesh("heavyPlasma")->SetVisible(false);
			
			auto ah = new AnimationHandlerDefaultUnit(go->GModel());
			go->GModel()->AnimationHandler.AddHandler(ah);
			go->SetUserData(ah);
#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 2.0f;
			botDesc.Radius = 1.8f;
			botDesc.MaxHealth = 30;
			botDesc.EntityType = ET_Bot;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);

			bot->GetBrain()->AddGoalAttackMove(dest);

			gameState->GetScene()->AddElement(go);
		}
		#pragma endregion

		#pragma region Member - Create - Player - Buildings
		void TikiBotFactory::CreatePlayerTower(GameObject* go)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"tower_mg"));
			//go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));
			go->PRS.SPosition() = GetPos(Vector2(go->PRS.GPosition().X, go->PRS.GPosition().Z), 10);

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 5.0f;
			botDesc.Radius = 2.0f;
			botDesc.MaxHealth = 100;
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Tower;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(2.0f);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->GetBrain()->AddGoalExplore();
			
			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerMainBuilding(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"building_main"));

			playerBase->MainBuilding = go;

			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 10.0f;
			botDesc.Radius = 5.0f;
			botDesc.MaxHealth = 100;	
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Building;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->SetScale(10.0f);

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerHeroPlatform(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"hero_platform"));

			playerBase->HeroPlatform = go;

			gameState->GetScene()->AddElement(go);
		}
		#pragma endregion

		#pragma region Member - Create - Player - Misc
		void TikiBotFactory::CreatePlayerSpiderMine(GameObject* go, TikiBot* target)
		{
			// Set Model
			go->SModel(gameState->GetEngine()->content->LoadModel(L"spidermine"));
			//go->GModel()->AnimationHandler.AddHandler(new AnimationHandlerDefaultUnit(go->GModel()));

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 0.33f;
			botDesc.Radius = 0.33f;
			botDesc.MaxHealth = 10;
			botDesc.MaxSpeed = 25;
			botDesc.EntityType = ET_Bot;

			TikiBot* bot = new TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);

			bot->GetTargetSys()->SetGlobalTarget(target);
			bot->GetBrain()->AddGoalAttackTarget();

			gameState->GetScene()->AddElement(go);
		}
		#pragma endregion

		#pragma region Member - Create - BuildSlot
		void TikiBotFactory::CreateBuildSlot(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"replaceme_cube"));
			go->PRS.SPosition() = GetPos(Vector2(go->PRS.GPosition().X, go->PRS.GPosition().Z), 10);
			//go->PRS.SScale() = Vector3(0.01f);

			new BuildSlot(gameState, go);
			gameState->GetScene()->AddElement(go);
		}
		#pragma endregion

		#pragma region Member - GetPos
		Vector3 TikiBotFactory::GetPos(const Vector2& pos, float heightAdjust)
		{
			Vector3 outPos;
			outPos.X = pos.X;
			outPos.Z = pos.Y;

			outPos.Y = gameState->GetScene()->GLevel()->GetTerrain()->SampleHeight(outPos);
			outPos.Y += heightAdjust;

			return outPos;
		}

		Vector3 TikiBotFactory::GetPos(const Vector3& pos, float heightAdjust)
		{
			return GetPos(pos.XZ(), heightAdjust);
		}
		#pragma endregion
	}
}
