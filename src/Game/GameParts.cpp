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

		void GamePart::Draw(const DrawArgs& args) {}
		void GamePart::Update(const UpdateArgs& args) {}
		#pragma endregion
	
		#pragma region EnemyBase
		EnemyBase::EnemyBase(GameState* state)
			: GamePart(state), Id(0), SpawnPoint(0), GateControl(0)
		{
		}

		EnemyBase::~EnemyBase()
		{
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
		#pragma endregion
	}
}