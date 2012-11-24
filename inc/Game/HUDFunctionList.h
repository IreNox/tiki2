#pragma once

#include "Game/HUDBase.h"

namespace TikiEngine
{
	namespace Game
	{
		class HUDFunctionList : public HUDBase
		{
		public:

			HUDFunctionList(GameState* state);
			~HUDFunctionList();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		};
	}
}