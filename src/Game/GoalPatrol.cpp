#include "Game/GoalPatrol.h"

#include "Game/GoalTypes.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalAttackTarget.h"

#include "Game/WeaponSystem.h"
#include "Game/Weapon.h"
namespace TikiEngine
{
	namespace AI
	{
		GoalPatrol::GoalPatrol(TikiBot* bot, std::list<Vector2> wayPoints)
			: GoalComposite<TikiBot>(bot, Goal_Patrol),
			path(wayPoints)
		{
			currWp = Vector2::Zero;
            lastWp = currWp;
            timeWpLeft = 0;
			attacking = false;

		}


		void GoalPatrol::Activate(const UpdateArgs& args)
		{
			status = Active;

			// if we have no target present, patrol to the next point
			if (!owner->GetTargetSys()->IsTargetPresent())
			{
                if  (attacking == true)
                {
                    attacking = false;
                    currWp = lastWp;
                    owner->GetEngine()->HLog.Write("set currWp to last. \n");
                }
                else
                {
                    lastWp = currWp;
                    currWp = path.front();
                    path.pop_front();
                    owner->GetEngine()->HLog.Write("set currWp and popped front. \n");
                }
				

				AddSubgoal(new GoalMoveToPosition(owner, Vector3(currWp.X, 0, currWp.Y)));
			}
			else
			{
                if (timeWpLeft == 0)
                    timeWpLeft = args.Time.TotalTime;

                if (args.Time.TotalTime - timeWpLeft > 5.0f)
                {
                    timeWpLeft = 0;
                    status = Completed;
                    return;
                }


				if (attacking == false)
				{
					attacking = true;
                    RemoveAllSubgoals();
                    owner->GetEngine()->HLog.Write("Target in range while patrolling. Attacking. \n");
                    AddSubgoal(new GoalAttackTarget(owner));
				}
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