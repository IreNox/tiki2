#pragma once

namespace TikiEngine
{
	namespace AI
	{
		class TikiBot;

		// interface for objects that are able to evaluate the desirability of 
		// a specific strategy level goal
		class GoalEvaluator
		{
		public:
			GoalEvaluator(float charBias)
				: characterBias(charBias) { }

			virtual ~GoalEvaluator() { }

			// returns a score between 0 and 1 representing the desirability of the
			// strategy the concrete subclass represents
			virtual float CalculateDesirability(TikiBot* bot)=0;

			//adds the appropriate goal to the given bot's brain
			virtual void SetGoal(TikiBot* bot) = 0;


		protected:
			// when the desirability score for a goal has been evaluated it is multiplied 
			// by this value. It can be used to create bots with preferences based upon their personality
			float characterBias;
		};
	}
}

