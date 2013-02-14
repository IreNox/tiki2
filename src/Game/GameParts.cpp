#pragma once

#include "Game/GamePart.h"
#include "Game/EnemyBase.h"
#include "Game/PlayerBase.h"

#include "Game/TikiBot.h"
#include "Game/GameState.h"
#include "Game/SkillSystem.h"
#include "Game/TikiBotFactory.h"

#include "Game/GD.h"
#include "Game/SceneLevel.h"
#include "Game/GoalThink.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region GamePart
		GamePart::GamePart(GameState* state)
			: EngineObject(state->GetEngine()), gameState(state), id(0)
		{
		}

		GamePart::~GamePart()
		{
		}

		void GamePart::Init() {}
		void GamePart::Draw(const DrawArgs& args) {}
		void GamePart::Update(const UpdateArgs& args) {}
		#pragma endregion
	
		#pragma region EnemyBase
		EnemyBase::EnemyBase(GameState* state)
			: GamePart(state), SpawnPoint(0), GateControl(0), baseAlive(true)
		{
		}

		EnemyBase::~EnemyBase()
		{
		}

		void EnemyBase::Init()
		{
#if _DEBUG
			if (this->GateControl == 0 || this->SpawnPoint == 0 || WayPoints.Count() == 0)
			{
				engine->HLog.Write("Enemy Base Definition failed");
			}
#endif

			this->GateControl->GetComponent<TikiBot>()->OnDeath.AddHandler(this);
		}

		void EnemyBase::Update(const UpdateArgs& args)
		{

		}

		void EnemyBase::Handle(TikiBot* sender, const BotDeadArgs& args)
		{
			baseAlive = false;
		}

		void EnemyBase::Spawn(bool enemy, bool player, const Vector2& playerPos)
		{
			if (!baseAlive) return;

			Vector3 pos = gameState->GetBotFactory()->GetPos(this->SpawnPoint->GPosition(),  3);

			if (enemy)
			{
				GameObject* go = TIKI_NEW GameObject(gameState->GetEngine());
				go->PRS.SPosition() = pos;
				gameState->GetBotFactory()->CreateEnemyMobHeavy(go, this->WayPoints);
			}

			if (player)
			{
				Vector2 pos2 = playerPos + Vector2(Random(-2, 2), Random(-2, 2));

				GameObject* go = TIKI_NEW GameObject(gameState->GetEngine());
				go->PRS.SPosition() = gameState->GetBotFactory()->GetPos(pos2, 3);
				gameState->GetBotFactory()->CreatePlayerMob(go, pos);
			}
		}
		#pragma endregion

		#pragma region PlayerBase
		#pragma region Class
		PlayerBase::PlayerBase(GameState* state)
			: GamePart(state), SpawnPoint(0), Hero(0), MainBuilding(0), heroDead(false), heroDeadTimer(10.0f),
			  attmodHealthReg(TA_HealthRegPercent, AMT_PerValue, 10, 0)
		{
		}

		PlayerBase::~PlayerBase()
		{
			SafeRelease(&Hero);
		}
		#pragma endregion

		#pragma region Init
		void PlayerBase::Init()
		{
#if _DEBUG
			if (this->MainBuilding == 0 || this->HeroPlatform == 0)
			{
				engine->HLog.WriteError("Player Base Definition failed", 0);
			}
#endif

			heroStartPos = HeroPlatform->PRS.GPosition() + Vector3(0, 0.2f, 0);

			ISphereCollider* platformTrigger = engine->librarys->CreateComponent<ISphereCollider>(HeroPlatform);

			platformTrigger->TriggerEnter.AddHandler(this);
			platformTrigger->TriggerExit.AddHandler(this);

			platformTrigger->SetCenter(heroStartPos);
			platformTrigger->SetMaterial(gameState->GetDefaultMaterial());
			platformTrigger->SetRadius(12.0f);
			platformTrigger->SetDynamic(false);
			platformTrigger->SetGroup(CG_Collidable_Non_Pushable);
			platformTrigger->SetTrigger(true);

			SafeAddRef(TIKI_NEW GameObject(engine), &Hero);
			gameState->GetBotFactory()->CreatePlayerHero(Hero);
			Hero->GetComponent<TikiBot>()->GetController()->SetCenter(gameState->GetBotFactory()->GetPos(heroStartPos, 10.0f));
			
			this->Hero->GetComponent<TikiBot>()->OnDeath.AddHandler(this);
			this->MainBuilding->GetComponent<TikiBot>()->OnDeath.AddHandler(this);
		}
		#pragma endregion

		#pragma region Member - Update
		void PlayerBase::Update(const UpdateArgs& args)
		{
			if (heroDead && heroDeadTimer.IsReady(args.Time))
			{				
				TikiBot* hero = Hero->GetComponent<TikiBot>();

				gameState->DecrementResource(
					HERO_CALC_DEADPRICE(gameState->GetResource(), hero->GetSkillSys()->GetLevel())
				);

                hero->GetBrain()->RemoveAllSubgoals();
				hero->Teleport(heroStartPos);
                hero->SetAlive();
                hero->RestoreHealthToMaximum();
				gameState->GetScene()->AddElement(Hero);
				heroDead = false;
			}
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void PlayerBase::Handle(TikiBot* sender, const BotDeadArgs& args)
		{
			if (sender->GetGameObject() == Hero)
			{
				heroDeadTimer.Reset();
				heroDeadTimer.Interval = HERO_CALC_DEADTIME(sender->GetSkillSys()->GetLevel());
				heroDead = true;
			}
			else if (sender->GetGameObject() == MainBuilding)
			{
				engine->Exit();
			}
		}

		void PlayerBase::Handle(ICollider* sender, const TriggerEnterArgs& args)
		{
			TikiBot* bot = args.otherCollider->GetGameObject()->GetComponent<TikiBot>();

			if (bot != 0 && bot->EntityType() == ET_Hero)
			{
				bot->GetAttSys().AddModifier(&attmodHealthReg);
			}
		}

		void PlayerBase::Handle(ICollider* sender, const TriggerExitArgs& args)
		{
			TikiBot* bot = args.otherCollider->GetGameObject()->GetComponent<TikiBot>();

			if (bot != 0 && bot->EntityType() == ET_Hero)
			{
				bot->GetAttSys().RemoveModifier(&attmodHealthReg);
			}
		}
		#pragma endregion
		#pragma endregion
	}
}