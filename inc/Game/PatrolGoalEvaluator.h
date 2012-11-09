#pragma once

#include "Game/GoalEvaluator.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		// class to calculate how desirable the goal of exploring is
		class PatrolGoalEvaluator : public GoalEvaluator
		{
		public:
			PatrolGoalEvaluator(float charBias);

			float CalculateDesirability(TikiBot* bot);

			// sets the Patrol goal
			void SetGoal(TikiBot* bot);
		};
	}
}