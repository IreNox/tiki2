#pragma once

#include "Core/Component.h"
#include "Game/GameState.h"


namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Components;
		using namespace TikiEngine::Game;

		class BuildSlot : public Component
		{

		public:
			BuildSlot(GameState* gameState, GameObject* gameObject);
			~BuildSlot();

			void Draw(const DrawArgs& args) {}
			void Update(const UpdateArgs& args) {}
			bool GetReady() { return true; }

			void Disable(); 
			bool Enabled();

		private:
			GameState* gameState;
			bool enabled;

		};


	}
}