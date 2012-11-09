#include "Game/PatrolGoalEvaluator.h"

#include "Game/GoalThink.h"

namespace TikiEngine
{
	namespace AI
	{
		PatrolGoalEvaluator::PatrolGoalEvaluator(float charBias)
			: GoalEvaluator(charBias)
		{
		}

		float PatrolGoalEvaluator::CalculateDesirability(TikiBot* bot)
		{

			float desirability = 0.0f;
			if (bot->GetBrain()->HasWayPoints())
			{
				desirability = 1.0f;

			}

			desirability *= characterBias;
			return desirability;
		}

		void PatrolGoalEvaluator::SetGoal(TikiBot* bot)
		{
			bot->GetBrain()->AddGoalPatrol(bot->GetBrain()->GetWaypoints());
		}

	}
}