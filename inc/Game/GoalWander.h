#pragma once

#include "Game/Goal.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		class GoalWander : public Goal<TikiBot>
		{

		public:
			GoalWander(TikiBot* bot);

			void Activate();
			int Process();
			void Terminate();
		};

	}
}