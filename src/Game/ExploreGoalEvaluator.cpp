#include "Game/ExploreGoalEvaluator.h"

#include "Game/GoalThink.h"

namespace TikiEngine
{
	namespace AI
	{
		ExploreGoalEvaluator::ExploreGoalEvaluator(float charBias)
			: GoalEvaluator(charBias)
		{
		}

		float ExploreGoalEvaluator::CalculateDesirability(TikiBot* bot)
		{
			float desirability = 0.05f;
			desirability *= characterBias;
			return desirability;
		}

		void ExploreGoalEvaluator::SetGoal(TikiBot* bot)
		{
			bot->GetBrain()->AddGoalExplore();
		}

	}
}