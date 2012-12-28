#pragma once

#include "Game/GamePart.h"
#include "Game/EnemyBase.h"
#include "Game/PlayerBase.h"

#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region GamePart
		GamePart::GamePart(GameState* state)
			: EngineObject(state->GetEngine()), gameState(state)
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
			: GamePart(state), SpawnPoint(0), GateControl(0)
		{
		}

		EnemyBase::~EnemyBase()
		{
		}

		void EnemyBase::Init()
		{
#if _DEBUG
			if (this->GateControl == 0 || this->SpawnPoint == 0)
			{
				engine->HLog.Write("Enemy Base Definition failed");
			}
#endif

			//this->GateControl->GetComponent<TikiBot>()->OnDeath.AddHandler(this);
		}
		#pragma endregion

		#pragma region PlayerBase
		PlayerBase::PlayerBase(GameState* state)
			: GamePart(state), SpawnPoint(0), MainBuilding(0)
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

			//this->Hero->GetComponent<TikiBot>()->OnDeath.AddHandler(this);
			//this->MainBuilding->GetComponent<TikiBot>()->OnDeath.AddHandler(this);
		}
		#pragma endregion
	}
}