#include "Game/GoalAttackTarget.h"

#include "Game/GoalHuntTarget.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalTypes.h"


namespace TikiEngine
{
	namespace AI
	{

		GoalAttackTarget::GoalAttackTarget(TikiBot* bot)
			: GoalComposite<TikiBot>(bot, Goal_Attack_Target)
		{
		}

		void GoalAttackTarget::Activate(const UpdateArgs& args)
		{
			status = Active;

			// if this goal is reactivated then there may be some existing subgoals that must be removed
			RemoveAllSubgoals();

			// it is possible for a bot's target to die whilst this goal is active 
			// so we must test to make sure the bot always has an active target
			if (!owner->GetTargetSys()->IsTargetPresent())
			{
				OutputDebugString(L"no target to attack (GoalAttackTarget). \n");
				status = Completed;
				return;
			}

			// if the bot is able to shoot the target (there is LOS between bot and
			// target), then select a tactic to follow while shooting
			if (owner->GetTargetSys()->IsTargetShootable()) //&&  dist > weaponRange)
			{
				// TODO: ShootAt() owner->GetTargetBot()->Pos();


				//OutputDebugString(L"Target Shootable:  PEW PEW ! \n");
				//owner->GetTargetBot()->GetBrain()->AddGoalAttackTarget();
			}
			else
			{
				// if the target is not visible, go hunt it.
				//OutputDebugString(L"Target not shootable. Hunting it. \n");
				//AddSubgoal(new GoalHuntTarget(owner));
			}

		}

		int GoalAttackTarget::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);

			 // process the subgoals
			status = ProcessSubgoals(args);

			ReactivateIfFailed();

			return status;
		}

		void GoalAttackTarget::Terminate()
		{
			status = Completed;
		}


	}
}