#include "Game/GoalMoveToPosition.h"

#include "Game/GoalSeekToPosition.h"
#include "Game/GoalFollowPath.h"
#include "Game/GoalTypes.h"


#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace AI
	{
		GoalMoveToPosition::GoalMoveToPosition(TikiBot* bot, Vector3 dest)
			: GoalComposite<TikiBot>(bot, Goal_Move_To_Position)
		{
			this->destination = dest;
		}


		void GoalMoveToPosition::Activate(const UpdateArgs& args)
		{
			status = Active;

			// make sure subgoal list is clear
			RemoveAllSubgoals();

            owner->GetEngine()->HLog.Write("GoalMoveToPosition - Raised Walk event.");
            owner->GetGameObject()->GModel()->animationEvent->RaiseEvent(owner->GetGameObject()->GModel(), AnimationArgs(Run));

			// requests a path to the target position from the path planner
			// if we can see the target, we just seek to it, else we use A* and path smoothing
			if (!owner->GetPathPlanner()->RequestPathTo(destination))
			{
				Vector2 t = Vector2(owner->GetPathPlanner()->GetTargetSnap().X,
									owner->GetPathPlanner()->GetTargetSnap().Z);
				AddSubgoal(new GoalSeekToPosition(owner, t));
				owner->GetEngine()->HLog.Write("has Path LOS - Seeking To position. \n");
			}
			else
			{
				owner->GetEngine()->HLog.Write("No Path LOS - path finding To position. \n");
				AddSubgoal(new GoalFollowPath(owner, owner->GetPathPlanner()->GetPath(true)));
			}
		}
		
		int GoalMoveToPosition::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);

			// process the subgoals
			status = ProcessSubgoals(args);

			// if any of the subgoals have failed then this goal re-plans
			ReactivateIfFailed();

			return status;
		}

		void GoalMoveToPosition::Draw(const DrawArgs& args)
		{
			//forward the request to the subgoals
			GoalComposite<TikiBot>::Draw(args);

#if _DEBUG
			// Draw target pos to move to
			Vector3 start = destination - Vector3(1.0f, 0, 0) + Vector3(0, 0, 1.0f);
			Vector3 end =	destination + Vector3(1.0f, 0, 0) - Vector3(0, 0, 1.0f);
			args.Graphics->DrawLine(start, end, Color::Red);

			start = destination - Vector3(1.0f, 0, 0) - Vector3(0, 0, 1.0f);
			end =	destination + Vector3(1.0f, 0, 0) + Vector3(0, 0, 1.0f);
			args.Graphics->DrawLine(start, end, Color::Red);
#endif
		}

	}
}