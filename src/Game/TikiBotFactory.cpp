#include "Game/TikiBotFactory.h"

#include "Game/TikiBot.h"
#include "Game/GoalThink.h"
#include "Game/SceneLevel.h"
#include "Game/BuildSlot.h"
#include "Game/AnimationHandler.h"

#include "Game/SkillRocket.h"
#include "Game/SkillFlash.h"
#include "Game/SkillHealAura.h"
#include "Game/SkillSpiderMine.h"
#include "Game/SkillSystem.h"

#include "Game/WeaponSystem.h"
#include "Game/Weapon.h"

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
			  playerBase(0), amodBuildingLifeReg(TA_HealthRegValue, AMT_PerValue, 5, 0), amodHeroLifeReg(TA_HealthRegValue, AMT_PerValue, 4.7, 0),
			  amodHeroDamage(TA_WeaponDamage, AMT_PerValue, 0.0, 0), amodHeroAttackSpeed(TA_WeaponFireSpeed, AMT_PerValue, 0.0, 0),
			  amodHeroArmor(TA_Armor, AMT_PerValue, 0.0, 0)
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

			enemyBases.Clear();
			gameState->GetParts<EnemyBase>(enemyBases);
			FOREACH_PTR_CALL(enemyBases, Init())
		}
		#pragma endregion

		#pragma region Member - Update
		void TikiBotFactory::Update(const UpdateArgs& args)
		{
			gameTime = (UInt32)args.Time.TotalTime;

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
		void TikiBotFactory::CreateEnemyMob(GameObject* go, const List<Vector2>& wayPoints)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"unit_soldier"));
			go->GModel()->GetMesh("heavyPlasma")->SetVisible(false);			
			auto ah = TIKI_NEW AnimationHandlerMGUnit(go->GModel());
			go->GModel()->SetAnimationHandler(ah);
				

#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif
			
			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.Height = 2.0f;
			botDesc.Radius = 1.8f;
			botDesc.EntityType = ET_Bot;

			float upgrades = (float)(gameTime / 180);

			botDesc.MaxHealth = 280.0f + (20.0f * upgrades);
			botDesc.StartMGDamage = 15 + (4.0f * upgrades);
			botDesc.StartMGFireRate = 0.67f;
			botDesc.MaxSpeed = 3.25f;
			botDesc.Armor = (1.25f * upgrades);

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);

			if (wayPoints.Count() != 0)
			{
				bot->GetBrain()->RemoveAllSubgoals();
				bot->GetBrain()->QueueGoalAttackMove(GetPos(wayPoints[0], 0.05f));
			}

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreateEnemyMobHeavy(GameObject* go, const List<Vector2>& wayPoints)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"unit_soldier"));
			go->GModel()->GetMesh("standartMG")->SetVisible(false);			
			auto ah = TIKI_NEW AnimationHandlerPlasmaUnit(go->GModel());
			go->GModel()->SetAnimationHandler(ah);


#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.Height = 2.0f;
			botDesc.Radius = 1.8f;
			botDesc.EntityType = ET_Bot;

			float upgrades = (float)(gameTime / 180);

			botDesc.MaxHealth = 280.0f + (15.0f * upgrades);
			botDesc.StartMGDamage = 18 + (2.0f * upgrades);
			botDesc.StartMGFireRate = 0.67f;
			botDesc.MaxSpeed = 3.25f;
			botDesc.Armor = (1.25f * upgrades);

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
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
			botDesc.Radius = 2.0f;
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Tower;

			botDesc.MaxHealth = 1550.0f;
			botDesc.StartMGDamage = 152;
			botDesc.StartMGFireRate = 1.083f;
			botDesc.Armor = 200;

			go->PRS.SPosition() = GetPos(Vector2(go->PRS.GPosition().X, go->PRS.GPosition().Z), 4.0f);

#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->GetBrain()->AddGoalExplore();

			gameState->GetScene()->AddElement(go);
		}


		void TikiBotFactory::CreateEnemyBuilding( GameObject* go )
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"gatecontrol"));

			TikiBotDescription botDesc;
			botDesc.Faction = 1;
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Building;
			botDesc.Height = 8.0f;
			botDesc.Radius = 8.0f; //5.0f;

			botDesc.MaxHealth = 5000;

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->SetScale(0.01f);
			bot->GetAttSys().AddModifier(&amodBuildingLifeReg);

#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			gameState->GetScene()->AddElement(go);
		}

		#pragma endregion

		#pragma region Member - Create - Player - Units
		void TikiBotFactory::CreatePlayerHero(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"unit_hero"));
			go->GModel()->GetMesh("Laser")->SetVisible(false);
			auto ah = TIKI_NEW AnimationHandlerHero(go->GModel());
			go->GModel()->SetAnimationHandler(ah);
				

#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 2.0f;
			botDesc.Radius = 1.8f;
			botDesc.EntityType = ET_Hero;

			botDesc.Armor = 18.0f;
			botDesc.MaxHealth = 395;
			botDesc.MaxSpeed = 3.95f * 2;
			botDesc.StartMGDamage = 47.5f * 1.5f;
			botDesc.StartMGFireRate = 0.625f;

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);

			bot->GetAttSys().AddModifier(&amodHeroArmor);
			bot->GetAttSys().AddModifier(&amodHeroDamage);
			bot->GetAttSys().AddModifier(&amodHeroLifeReg);
			bot->GetAttSys().AddModifier(&amodHeroAttackSpeed);
			
			bot->GetSkillSys()->AddSkill(TIKI_NEW SkillFlash(bot));
			bot->GetSkillSys()->AddSkill(TIKI_NEW SkillRocket(bot));
			bot->GetSkillSys()->AddSkill(TIKI_NEW SkillHealAura(bot));
			bot->GetSkillSys()->AddSkill(TIKI_NEW SkillSpiderMine(bot));

			bot->GetSkillSys()->LevelUp.AddHandler(this);

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerMob(GameObject* go, const Vector3& dest)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"unit_marine"));
			go->GModel()->GetMesh("heavyPlasma")->SetVisible(false);
			go->GModel()->GetMesh("LP_Backpack")->SetVisible(false);

			auto ah = TIKI_NEW AnimationHandlerMGUnit(go->GModel());
			go->GModel()->SetAnimationHandler(ah);


#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 2.0f;
			botDesc.Radius = 1.8f;

			float upgrades = (float)(gameTime / 180);

			botDesc.MaxHealth = 280.0f + (15.0f * upgrades);
			botDesc.StartMGDamage = 20 + (2.0f * upgrades);
			botDesc.StartMGFireRate = 0.67f;
			botDesc.MaxSpeed = 3.25f;
			botDesc.Armor = (3.0f * upgrades);

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);

			bot->GetBrain()->AddGoalAttackMove(dest);

			gameState->GetScene()->AddElement(go);
		}
		
		void TikiBotFactory::CreatePlayerMobHeavy(GameObject* go, const Vector3& destination)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"unit_marine"));
			go->GModel()->GetMesh("standartMG")->SetVisible(false);

			auto ah = TIKI_NEW AnimationHandlerPlasmaUnit(go->GModel());
			go->GModel()->SetAnimationHandler(ah);


#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 2.0f;
			botDesc.Radius = 1.8f;

			float upgrades = (float)(gameTime / 180);

			botDesc.MaxHealth = 280.0f + (15.0f * upgrades);
			botDesc.StartMGDamage = 25 + (2.0f * upgrades);
			botDesc.StartMGFireRate = 0.67f;
			botDesc.MaxSpeed = 3.25f;
			botDesc.Armor = (1.25f * upgrades);

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);

			bot->GetBrain()->AddGoalAttackMove(destination);

			gameState->GetScene()->AddElement(go);
		}

		#pragma endregion

		#pragma region Member - Create - Player - Buildings
		void TikiBotFactory::CreatePlayerTower(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"tower_player"));

#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 5.0f;
			botDesc.Radius = 2.0f;
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Tower;

			botDesc.MaxHealth = 1550.0f;
			botDesc.StartMGDamage = 152;
			botDesc.StartMGFireRate = 1.083f;
			botDesc.Armor = 200;

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->SetScale(0.01f);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->GetBrain()->AddGoalExplore();
			
			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerMainBuilding(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"mainbuilding"));
			auto ah = TIKI_NEW AnimationHandlerPlayerBase(go->GModel());
			go->GModel()->SetAnimationHandler(ah);


			playerBase->MainBuilding = go;

			TikiBotDescription botDesc;
			botDesc.Armor = 5;
			botDesc.Faction = 0;
			botDesc.Height = 10.0f;
			botDesc.Radius = 5.0f;
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Building;

			botDesc.MaxHealth = 5500;

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->SetScale(0.01f);
			bot->GetAttSys().AddModifier(&amodBuildingLifeReg);

#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerHeroPlatform(GameObject* go)
		{
			go->PRS.SScale() = 0.01f;
			go->SModel(gameState->GetEngine()->content->LoadModel(L"heroplatform"));

			playerBase->HeroPlatform = go;

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerSpawnBuilding(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"base_spawn"));
			
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 10.0f;
			botDesc.Radius = 5.0f;
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Building;

			botDesc.MaxHealth = 4000.0f;

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->SetScale(0.01f);

			gameState->GetScene()->AddElement(go);
		}

		void TikiBotFactory::CreatePlayerResearchBuilding(GameObject* go)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"base_radar"));

			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 10.0f;
			botDesc.Radius = 5.0f;
			botDesc.MaxSpeed = 0.000001f;
			botDesc.EntityType = ET_Building;

			botDesc.MaxHealth = 2000.0f;

			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->GetController()->SetGroup(CG_Collidable_Non_Pushable);
			bot->SetScale(0.01f);

			gameState->GetScene()->AddElement(go);
		}
		#pragma endregion

		#pragma region Member - Create - Player - Misc
		void TikiBotFactory::CreatePlayerSpiderMine(GameObject* go, const Vector3& target)
		{
			go->SModel(gameState->GetEngine()->content->LoadModel(L"spidermine"));

			auto ah = TIKI_NEW AnimationHandlerSpidermine(go->GModel());
			go->GModel()->SetAnimationHandler(ah);

#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			// Create bot
			TikiBotDescription botDesc;
			botDesc.Faction = 0;
			botDesc.Height = 2.0f;
			botDesc.Radius = 1.8f;
			botDesc.MaxHealth = 200;
			botDesc.StartMGDamage = 5;
			botDesc.EntityType = ET_Bot;
			botDesc.StartMGFireRate = 5;
			botDesc.MaxSpeed = 15.0f;
			
			TikiBot* bot = TIKI_NEW TikiBot(gameState, go, botDesc);
			bot->SetSpiderMine();
			bot->SetScale(0.01f);
			bot->GetWeaponSys()->GetCurrentWeapon()->SetRange(10.0f);
			//bot->GetTargetSys()->SetGlobalTarget(target);
			bot->GetBrain()->AddGoalAttackMove(target);

			gameState->GetScene()->AddElement(go);
			
		}
		#pragma endregion

		#pragma region Member - Create - BuildSlot
		void TikiBotFactory::CreateBuildSlot(GameObject* go)
		{
			go->PRS.SScale() = Vector3(0.01f);
			go->PRS.SPosition() = GetPos(Vector2(go->PRS.GPosition().X, go->PRS.GPosition().Z), 0.13f);
			go->SModel(gameState->GetEngine()->content->LoadModel(L"buildpoint"));

#if TIKI_USE_SCENEGRAPH
			go->GetSceneGraphElement().SetDynamic();
#endif

			TIKI_NEW BuildSlot(gameState, go);
			gameState->GetScene()->AddElement(go);
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void TikiBotFactory::Handle(TikiBot* sender, const HeroLevelUpEventArgs& args)
		{
			amodHeroArmor.SetValue(3.5f * args.HeroLevel);
			sender->GetAttSys().UpdateModifier(&amodHeroArmor);
			//args.
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
