#include "Game/GoalThink.h"

#include "Game/GoalTypes.h"
#include "Game/GoalExplore.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalAttackTarget.h"
#include "Game/GoalAttackMove.h"
#include "Game/GoalPatrol.h"
#include "Game/GoalAttackGlobalTarget.h"


#include "Game/AttackTargetGoalEvaluator.h"
#include "Game/ExploreGoalEvaluator.h"
#include "Game/PatrolGoalEvaluator.h"

#include <cassert>

namespace TikiEngine
{
	namespace AI
	{


		GoalThink::GoalThink(TikiBot* bot)
			: GoalComposite<TikiBot>(bot, Goal_Think)
		{
			hasWaypoints = false;
			attackTargetRegulator = TIKI_NEW Regulator(3);

            bot->GetGameObject()->GModel()->AnimationHandler->RaiseAnimationEvent(bot->GetGameObject()->GModel(), AnimationArgs(AT_Idle));
		}

		GoalThink::~GoalThink()
		{
			// remove evaluators
			GoalEvaluators::iterator curDes = evaluators.begin();
			for (curDes; curDes != evaluators.end(); ++curDes)
				SafeDelete(&(*curDes));

			// remove regulator
			SafeDelete(&attackTargetRegulator);

		}

		void GoalThink::Init(float exploreBias, float attackBias, float patrolBias)
		{
			evaluators.push_back(TIKI_NEW ExploreGoalEvaluator(exploreBias));
			evaluators.push_back(TIKI_NEW AttackTargetGoalEvaluator(attackBias));
			evaluators.push_back(TIKI_NEW PatrolGoalEvaluator(patrolBias));
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
			//if (owner->GetFaction() == 1)//(!owner->IsPossessed())
				//Arbitrate();

			status = Active;
		}

		int GoalThink::Process(const UpdateArgs& args)
		{
			ActivateIfInactive(args);
			ProcessSubgoals(args);

			//if (subgoalStatus == Completed || subgoalStatus == Failed)
			//{
			//	if (owner->GetFaction() == 1) //(!owner->IsPossessed())
			//		status = Inactive;
			//}

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
				AddSubgoal(TIKI_NEW GoalExplore(owner));
			}
		}

		void GoalThink::AddGoalPatrol(const List<Vector2>& wps)
		{
			if (NotPresent(Goal_Patrol))
			{
				hasWaypoints = true;
				wayPoints = wps;

				RemoveAllSubgoals();
				AddSubgoal(TIKI_NEW GoalPatrol(owner, wps));
			}
		}

		void GoalThink::AddGoalAttackGlobalTarget(TikiBot* target)
		{
			RemoveAllSubgoals();
			AddSubgoal(TIKI_NEW GoalAttackGlobalTarget(owner, target, attackTargetRegulator));
		}

		void GoalThink::AddGoalAttackTarget()
		{
			if (NotPresent(Goal_Attack_Target))
			{
				RemoveAllSubgoals();
				AddSubgoal(TIKI_NEW GoalAttackTarget(owner));
			}
		}

		void GoalThink::AddGoalAttackMove(Vector3 pos)
		{
 			//if (NotPresent(Goal_Attack_Move))
 			//{
 				//RemoveAllSubgoals();
 				AddSubgoal(TIKI_NEW GoalAttackMove(owner, pos));
 			//}
		}

		void GoalThink::QueueGoalAttackMove(Vector3 pos)
		{
			subGoals.push_back(TIKI_NEW GoalAttackMove(owner, pos));
		}

		void GoalThink::AddGoalMoveToPosition(Vector3 pos)
		{
			AddSubgoal( TIKI_NEW GoalMoveToPosition(owner, pos));
		}

		void GoalThink::QueueGoalMoveToPosition(Vector3 pos)
		{
			subGoals.push_back(TIKI_NEW GoalMoveToPosition(owner, pos));
		}


	}
}