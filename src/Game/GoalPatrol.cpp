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
		GoalPatrol::GoalPatrol(TikiBot* bot, const List<Vector2>& wayPoints)
			: GoalComposite<TikiBot>(bot, Goal_Patrol), path(wayPoints)
		{
			currWp = path[0];
            //timeWpLeft = 0;
			attacking = false;
		}

		void GoalPatrol::Activate(const UpdateArgs& args)
		{
			status = Active;

			RemoveAllSubgoals();

			// if we have no target present, patrol to the next point
			if (!owner->GetTargetSys()->IsTargetPresent())
			{
                if  (attacking == true)
                {
                    attacking = false;
                }
                else
                {
                    currWp = path[0];
                    path.RemoveAt(0);
                   // owner->GetEngine()->HLog.Write("GoalPatrol - set currWp and popped front. \n");
                }
				
				AddSubgoal(TIKI_NEW GoalMoveToPosition(owner, Vector3(currWp.X, 0, currWp.Y)));
			}
			else
			{
     //           if (timeWpLeft == 0)
     //               timeWpLeft = args.Time.TotalTime;

     //           if (args.Time.TotalTime - timeWpLeft > 5.0f)
     //           {
     //               timeWpLeft = 0;
					//attacking = false;
     //               return;
     //           }

				if (attacking == false)
				{
                    AddSubgoal(TIKI_NEW GoalAttackTarget(owner));
                    attacking = true;
                    //owner->GetEngine()->HLog.Write("GoalPatrol - Target in range while patrolling. Attacking. Raised Attack event. \n");
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
			else if (status == Completed && path.Count() != 0)
				Activate(args);

			return status;
		}

		void GoalPatrol::Draw(const DrawArgs& args)
		{
			GoalComposite<TikiBot>::Draw(args);
		}
	}
}