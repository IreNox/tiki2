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

			void Activate(const UpdateArgs& args);
			int Process(const UpdateArgs& args);
			void Terminate();
		};

	}
}