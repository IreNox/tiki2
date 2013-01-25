#include "Game/GoalAttackMove.h"

#include "Game/GoalTypes.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalAttackTarget.h"

namespace TikiEngine
{
	namespace AI
	{
		GoalAttackMove::GoalAttackMove(TikiBot* owner, Vector3 dest)
			:GoalComposite<TikiBot>(owner, Goal_Attack_Move)
		{
			this->destination = dest;
			attacking = false;
		}

		void GoalAttackMove::Activate(const UpdateArgs& args)
		{
			status = Active;

			// if this goal is reactivated then there may be some existing subgoals that must be removed
			RemoveAllSubgoals();

			// move to the random location
			if (owner->GetTargetSys()->IsTargetPresent())
			{
				if (attacking == false)
				{
					attacking = true;
					//owner->GetEngine()->HLog.Write("AttackMove - Attacking. \n");
					AddSubgoal(TIKI_NEW GoalAttackTarget(owner));
				}

			}
			else
			{
				attacking = false;
				//owner->GetEngine()->HLog.Write("AttackMove - Moving. \n");
				AddSubgoal(TIKI_NEW GoalMoveToPosition(owner, destination));
			}
		}


		int GoalAttackMove::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);

			// process the subgoals
			status = ProcessSubgoals(args);

			// just set the state to inactive, so it always gets reactivated if there's some target to shoot to
 			if (owner->GetTargetSys()->IsTargetPresent())
 			{
 				status = Inactive;
 			}

			return status;
		}

	}
}