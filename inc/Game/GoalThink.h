#pragma once

#include "Game/GoalComposite.h"
#include "Game/TikiBot.h"
#include "Game/GoalEvaluator.h"

namespace TikiEngine
{
	namespace AI
	{

		class GoalThink : public GoalComposite<TikiBot>
		{

		public:
			GoalThink(TikiBot* bot);
			~GoalThink();

			// arbitrate between available strategies, choosing the most appropriate to be pursued.
			void Arbitrate();

			#pragma region GoalComposite 
			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate() { }
			void Draw(const DrawArgs& args);
			#pragma endregion

			// returns true if the given goal is not at the front of the subgoal list
			bool NotPresent(unsigned int gt) const;

			// top level goal types
			void AddGoalExplore();
			void AddGoalAttackTarget();
			void AddGoalAttackMove(Vector3 pos);
			void AddGoalMoveToPosition(Vector3 pos);
			void QueueGoalMoveToPosition(Vector3 pos);

		private:
			typedef std::vector<GoalEvaluator*> GoalEvaluators;
			GoalEvaluators evaluators;
		};
	}
}