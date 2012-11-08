#include "Game/GoalThink.h"

#include "Game/GoalTypes.h"
#include "Game/GoalExplore.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalAttackTarget.h"
#include "Game/GoalAttackMove.h"


#include "Game/AttackTargetGoalEvaluator.h"
#include "Game/ExploreGoalEvaluator.h"

#include <cassert>

namespace TikiEngine
{
	namespace AI
	{


		GoalThink::GoalThink(TikiBot* bot)
			: GoalComposite<TikiBot>(bot, Goal_Think)
		{

			// load this from desc
			float ExploreBias = 0.05f;
			float AttackBias = 1.5f;
			

			evaluators.push_back(new ExploreGoalEvaluator(ExploreBias));
			evaluators.push_back(new AttackTargetGoalEvaluator(AttackBias));
		}

		GoalThink::~GoalThink()
		{
			// remove evaluators
			GoalEvaluators::iterator curDes = evaluators.begin();
			for (curDes; curDes != evaluators.end(); ++curDes)
				SafeDelete(&(*curDes));

		}

		void GoalThink::Arbitrate()
		{
			float best = 0;
			GoalEvaluator* mostDesirable = 0;

			// iterate through all the evaluators to see which produces the highest score

			GoalEvaluators::iterator curDes = evaluators.begin();
			for (curDes; curDes != evaluators.end(); ++curDes)
			{
				float desirability = (*curDes)->CalculateDesirability(owner);
				if (desirability >= best)
				{
					best = desirability;
					mostDesirable = *curDes;
				} // if
			} // for

			assert(mostDesirable && "<GoalThink::Arbitrate>: no Evaluator selected");

			mostDesirable->SetGoal(owner);
		}

		#pragma region GoalComposite 

		void GoalThink::Activate(const UpdateArgs& args)
		{
			if (!owner->IsPossessed())
			{
				Arbitrate();
			}

			status = Active;
		}

		int GoalThink::Process(const UpdateArgs& args)
		{
			ActivateIfInactive(args);

			int subgoalStatus = ProcessSubgoals(args);

			if (subgoalStatus == Completed || subgoalStatus == Failed)
			{
				if (!owner->IsPossessed())
					status = Inactive;
			}

			return status;
		}


		void GoalThink::Draw(const DrawArgs& args)
		{
			std::list<Goal<TikiBot>*>::iterator curGoal;
			for (curGoal = subGoals.begin(); curGoal != subGoals.end(); ++curGoal)
				(*curGoal)->Draw(args);
		}

		#pragma endregion
	
		bool GoalThink::NotPresent(unsigned int gt) const
		{
			if (!subGoals.empty())
				return subGoals.front()->GetType() != gt;

			return true;
		}
	
		void GoalThink::AddGoalExplore()
		{
			if (NotPresent(Goal_Explore))
			{
				RemoveAllSubgoals();
				AddSubgoal(new GoalExplore(owner));
			}
		}

		void GoalThink::AddGoalAttackTarget()
		{
			if (NotPresent(Goal_Attack_Target))
			{
				RemoveAllSubgoals();
				AddSubgoal(new GoalAttackTarget(owner));
			}
		}

		void GoalThink::AddGoalAttackMove(Vector3 pos)
		{
 			if (NotPresent(Goal_Attack_Move))
 			{
 				RemoveAllSubgoals();
 				AddSubgoal(new GoalAttackMove(owner, pos));
 			}

			//AddSubgoal(new GoalAttackMove(owner, pos));
			//subGoals.push_back(new GoalAttackMove(owner, pos));
		}

		void GoalThink::AddGoalMoveToPosition(Vector3 pos)
		{
			AddSubgoal( new GoalMoveToPosition(owner, pos));
		}

		void GoalThink::QueueGoalMoveToPosition(Vector3 pos)
		{
			subGoals.push_back(new GoalMoveToPosition(owner, pos));
		}


	}
}