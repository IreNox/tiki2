#include "Game/GoalPatrol.h"

#include "Game/GoalTypes.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalAttackTarget.h"

namespace TikiEngine
{
	namespace AI
	{
		GoalPatrol::GoalPatrol(TikiBot* bot, std::list<Vector2> wayPoints)
			: GoalComposite<TikiBot>(bot, Goal_Patrol),
			path(wayPoints)
		{
			currWp = Vector2::Zero;
		}


		void GoalPatrol::Activate(const UpdateArgs& args)
		{
			status = Active;

			// if this goal is reactivated then there may be some existing subgoals that must be removed
			RemoveAllSubgoals();

			// if we have no target present, patrol to the next point
			if (!owner->GetTargetSys()->IsTargetPresent())
			{
				currWp = path.front();
				path.pop_front();
				AddSubgoal(new GoalMoveToPosition(owner, Vector3(currWp.X, 0, currWp.Y)));
			}
			else
			{
				OutputDebugString(L"TargetShootable while patroling. Attacking. \n");
				AddSubgoal(new GoalAttackTarget(owner));
			}
		}

		int GoalPatrol::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);

			// process the subgoals
			status = ProcessSubgoals(args);

			// if we have a target, activate to attack. Otherwise if we have 
			// completed attacking and we still have a path continue patroling
 			if (owner->GetTargetSys()->IsTargetPresent())
				Activate(args);
			else if (status == Completed && !path.empty())
				Activate(args);

			return status;
		}

		void GoalPatrol::Draw(const DrawArgs& args)
		{
			GoalComposite<TikiBot>::Draw(args);
		}


	}
}