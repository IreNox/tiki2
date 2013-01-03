#pragma once

#include "Game/GamePart.h"

#include "Core/GameObject.h"
#include "Game/LevelPoint.h"

#include "Game/EventBotDead.h"

namespace TikiEngine
{
	namespace Game
	{
		class EnemyBase : public GamePart, public BotDeadEventHandler
		{
		public:

			LevelPoint* SpawnPoint;
			LevelPoint* PlayerSpawnPoint;

			GameObject* GateControl;

			List<Vector2> WayPoints;

			EnemyBase(GameState* state);
			~EnemyBase();

			void Init();
			void Update(const UpdateArgs& args);

			void Spawn(bool enemy, bool player, const Vector2& playerPos);

			void Handle(TikiBot* sender, const BotDeadArgs& args);

		private:

			bool baseAlive;

		};
	}
}