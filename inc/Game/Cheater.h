#pragma once

#include "Core/EngineObject.h"
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{
		class Cheater : public EngineObject
		{
		public:

			Cheater(GameState* state);
			~Cheater();

			void DoCheat(const wstring& cheat);

		private:

			GameState* gameState;

		};
	}
}