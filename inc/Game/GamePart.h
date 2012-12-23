#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	namespace Game
	{
		class GameState;

		class GamePart : public EngineObject
		{
		public:

			GamePart(GameState* state);
			~GamePart();

			virtual void Draw(const DrawArgs& args);
			virtual void Update(const UpdateArgs& args);

		protected:

			GameState* gameState;

		};
	}
}