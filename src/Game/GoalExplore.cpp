#include "Game/GoalExplore.h"

#include "Game/GoalTypes.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalAttackTarget.h"

namespace TikiEngine
{
	namespace AI
	{
		GoalExplore::GoalExplore(TikiBot* bot)
			: GoalComposite<TikiBot>(bot, Goal_Explore)
		{
			destinationIsSet = false;
		}

		void GoalExplore::Activate(const UpdateArgs& args)
		{
			status = Active;

			// if this goal is reactivated then there may be some existing subgoals that must be removed
			RemoveAllSubgoals();

			if (!destinationIsSet)
			{
				currentDestination = owner->GetPathPlanner()->GetRandomPosOnPath();
				destinationIsSet = true;
			}

			// move to the random location
			AddSubgoal(TIKI_NEW GoalMoveToPosition(owner, currentDestination));
		}

		int GoalExplore::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);

			// process the subgoals
			status = ProcessSubgoals(args);

			if (owner->GetTargetSys()->IsTargetWithinFOV() && owner->GetTargetSys()->IsTargetShootable())
			{
				//owner->GetEngine()->HLog.Write("Target Within FOV while exploring. Attacking it");
				AddSubgoal(TIKI_NEW GoalAttackTarget(owner));
				
				status = Completed;
			}

			return status;
		}

	}
}