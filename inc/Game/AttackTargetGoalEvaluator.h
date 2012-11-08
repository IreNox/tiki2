#pragma once

#include "Game/GoalEvaluator.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		class AttackTargetGoalEvaluator : public GoalEvaluator
		{
		public:
			AttackTargetGoalEvaluator(float charBias);

			//  returns a value between 0 and 1 that indicates the Rating of a bot 
			// (the higher the score, the stronger the bot).
			float CalculateDesirability(TikiBot* bot);

			// Sets Attack target goal
			void SetGoal(TikiBot* bot);
		};

	}
}