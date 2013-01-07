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
				GameObject* go = new GameObject(gameState->GetEngine());
				go->GetGameObjectType() = Dynamic;
				go->PRS.SPosition() = pos;
				gameState->GetBotFactory()->CreateEnemy1(go, this->WayPoints);
			}

			if (player)
			{
				GameObject* go = new GameObject(gameState->GetEngine());
				go->GetGameObjectType() = Dynamic;
				go->PRS.SPosition() = gameState->GetBotFactory()->GetPos(playerPos, 3);
				gameState->GetBotFactory()->CreatePlayerMop(go, pos);
			}
		}
		#pragma endregion

		#pragma region PlayerBase
		PlayerBase::PlayerBase(GameState* state)
			: GamePart(state), SpawnPoint(0), Hero(0), MainBuilding(0), heroDead(false), heroDeadTimer(10.0f)
		{
		}

		PlayerBase::~PlayerBase()
		{
		}

		void PlayerBase::Init()
		{
#if _DEBUG
			if (this->MainBuilding == 0 || this->Hero == 0)
			{
				engine->HLog.Write("Player Base Definition failed");
			}
#endif

			heroStartPos = Hero->PRS.GPosition() + Vector3(0, 0.2f, 0);

			this->Hero->GetComponent<TikiBot>()->OnDeath.AddHandler(this);
			this->MainBuilding->GetComponent<TikiBot>()->OnDeath.AddHandler(this);
		}

		void PlayerBase::Update(const UpdateArgs& args)
		{
            if (args.Input.GetKey(KEY_SPACE))
                Hero->GetComponent<TikiBot>()->ReduceHealth(1000);

			if (heroDead && heroDeadTimer.IsReady(args.Time))
			{
                TikiBot* hero = Hero->GetComponent<TikiBot>();
                hero->GetBrain()->RemoveAllSubgoals();
				hero->Teleport(heroStartPos);
                hero->SetAlive();
                hero->RestoreHealthToMaximum();
				gameState->GetScene()->AddElement(Hero);
				heroDead = false;
			}
		}

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
		#pragma endregion
	}
}