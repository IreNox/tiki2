#pragma once

#include "Game/GamePart.h"

#include "Core/GameObject.h"
#include "Game/LevelPoint.h"

#include "Game/EventBotDead.h"

#include "Core/TikiTimer.h"

namespace TikiEngine
{
	namespace Game
	{
		class PlayerBase : public GamePart, public BotDeadEventHandler
		{
		public:

			LevelPoint* SpawnPoint;

			GameObject* Hero;
			GameObject* MainBuilding;

			PlayerBase(GameState* state);
			~PlayerBase();
			
			void Init();

			void Update(const UpdateArgs& args);

			void Handle(TikiBot* sender, const BotDeadArgs& args);

		private:

			bool heroDead;
			TikiTimer heroDeadTimer;

			Vector3 heroStartPos;

		};
	}
}