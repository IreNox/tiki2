#pragma once

#include "Core/TypeInc.h"
#include "Core/Component.h"
#include "Core/GameObject.h"

#include "Game/Utils.h"
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Game;
		using namespace TikiEngine::Components;

		class BotRemove : public Component
		{
		public:
			BotRemove(GameState* gameState, GameObject* gameObject);
			~BotRemove() { }

			void Draw(const DrawArgs& args) { }
			void Update(const UpdateArgs& args);
			bool GetReady() { return true; }

		private:
			double timeTillDeath;
			GameState* gameState;
		};
	}
}