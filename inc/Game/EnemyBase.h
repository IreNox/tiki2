#pragma once

#include "Game/GamePart.h"

#include "Core/GameObject.h"
#include "Game/LevelPoint.h"

namespace TikiEngine
{
	namespace Game
	{
		class EnemyBase : public GamePart
		{
		public:

			LevelPoint* SpawnPoint;
			GameObject* GateControl;

			List<Vector2> WayPoints;

			EnemyBase(GameState* state);
			~EnemyBase();

			void Init();

		};
	}
}