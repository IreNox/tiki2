#include "Game/GoalAttackGlobalTarget.h"

#include "Game/GoalAttackTarget.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalTypes.h"


namespace TikiEngine
{
	namespace AI
	{
		GoalAttackGlobalTarget::GoalAttackGlobalTarget(TikiBot* bot, TikiBot* target, Regulator* reg)
			:GoalComposite<TikiBot>(bot, Goal_Attack_GlobalTarget)
		{
			this->target = target;
			this->attacking = false;
			owner->GetTargetSys()->SetGlobalTarget(target);

			attackTargetRegulator = reg;
		}


		void GoalAttackGlobalTarget::Activate(const UpdateArgs& args)
		{
			status = Active;



			// only update once per second
			if (attackTargetRegulator->IsReady())
			{
				// if this goal is reactivated then there may be some existing subgoals that must be removed
				RemoveAllSubgoals();

				// it is possible for a bot's target to die whilst this goal is active 
				// so we must test to make sure the bot always has an active target
				if (owner->GetTargetSys()->IsTargetShootable())
				{
					if (attacking == false)
					{
						owner->GetSteering()->SeekOff();
						owner->GetSteering()->ArriveOff();

                        owner->GetGameObject()->GModel()->animationEvent->RaiseEvent(owner->GetGameObject()->GModel(), AnimationArgs(Attack));


						target->GetEngine()->HLog.Write("GoalAttackGlobalTarget - Attacking. Raised Attack event \n");
						attacking = true;
					}

				}
				else
				{
					attacking = false;
					target->GetEngine()->HLog.Write("GoalAttackGlobalTarget - Moving to target \n");
					AddSubgoal(new GoalMoveToPosition(owner, target->Pos3D()));
				}
			}



		}

		int GoalAttackGlobalTarget::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);

			// process the subgoals
			status = ProcessSubgoals(args);

			if(target->IsAlive())
				status = Inactive;
			else
			{
				owner->GetTargetSys()->ClearGlobalTarget();
				target->GetEngine()->HLog.Write("GoalAttackGlobalTarget - Target dead or NUll. \n");
				status = Completed;
			}

			return status;
		}

		void GoalAttackGlobalTarget::Terminate()
		{
			//target->GetEngine()->HLog.Write("GoalAttackGlobalTarget - Terminate. \n");
			owner->GetTargetSys()->ClearGlobalTarget();
			status = Completed;
		}


	}
}