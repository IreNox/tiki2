#pragma once

#include "Game/GoalEvaluator.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		// class to calculate how desirable the goal of exploring is
		class ExploreGoalEvaluator : public GoalEvaluator
		{
		public:
			ExploreGoalEvaluator(float charBias);

			// go exploring the map if there are no other things requiring your immediate
			// attention like attacking an opponent or looking for ammo or health. Consequently,
			// the desirability of exploring the map is fixed as a low constant
			// value, thus ensuring the option to explore is only selected if all alternatives
			// have lower desirability scores
			float CalculateDesirability(TikiBot* bot);

			// sets the Explore goal
			void SetGoal(TikiBot* bot);
		};
	}
}