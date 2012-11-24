#pragma once

#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace Game
	{
		class GameState;

		class HUDBase : public GameObject
		{
		public:

			HUDBase(GameState* state);
			~HUDBase();

		protected:

			GameState* state;

		};
	}
}