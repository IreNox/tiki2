#include "Game/AttackTargetGoalEvaluator.h"

#include "Game/GoalThink.h"

namespace TikiEngine
{
	namespace AI
	{
		AttackTargetGoalEvaluator::AttackTargetGoalEvaluator(float charBias)
			: GoalEvaluator(charBias)
		{
		}

		float AttackTargetGoalEvaluator::CalculateDesirability(TikiBot* bot)
		{
			float desirability = 0.0f;

			// only do the calculation if there is a target present
			if (bot->GetTargetSys()->IsTargetPresent())
			{
				const float Tweaker = 1.0f;
				desirability = Tweaker;
				// TODO: Tweaker * health * weaponstrength


				//bias the value according to the personality of the bot
				desirability *= characterBias;

			}

			return desirability;
		}

		void AttackTargetGoalEvaluator::SetGoal(TikiBot* bot)
		{
			bot->GetBrain()->AddGoalAttackTarget();
		}

	}
}