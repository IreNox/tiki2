#pragma once

#include "Game/GoalComposite.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		class GoalAttackTarget : public GoalComposite<TikiBot>
		{

		public:
			GoalAttackTarget(TikiBot* bot);

			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate();
		};

	}
}