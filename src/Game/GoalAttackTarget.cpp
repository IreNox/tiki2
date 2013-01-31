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
				//owner->GetEngine()->HLog.Write("no target to attack (GoalAttackTarget). \n");
				status = Completed;
				owner->GetGameObject()->GModel()->AnimationHandler->RaiseAnimationEvent(owner->GetGameObject()->GModel(), AnimationArgs(AT_Idle));
				return;
			}
//             else
//             {
//                 owner->GetEngine()->HLog.Write("Raised Attack Animation. \n");
//                 owner->GetGameObject()->GModel()->animationEvent->RaiseEvent(owner->GetGameObject()->GModel(), AnimationArgs(Attack));
//             }
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
