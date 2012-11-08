#include "Game/GoalHuntTarget.h"

#include "Game/GoalTypes.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalExplore.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace AI
	{
		GoalHuntTarget::GoalHuntTarget(TikiBot* bot)
			: GoalComposite<TikiBot>(bot, Goal_Hunt_Target)
		{
			lvpTried = false;
		}

		void GoalHuntTarget::Activate(const UpdateArgs& args)
		{
			status = Active;

			// if this goal is reactivated, then there may be some existing subgoals that must be removed
			RemoveAllSubgoals();

			// it is possible for the target do die whilst this goal is active so we 
			// must test to make sure the bot always has an active target
			if (owner->GetTargetSys()->IsTargetPresent())
			{
				// grab a local copy of the last recorded position (LRP) of the target
				const Vector3 lrp = owner->GetTargetSys()->GetLastRecordedPosition();
				const Vector2 lrp2D = Vector2(lrp.X, lrp.Z);

				// if the bot has reached the lrp and it still hasn't found the target,
				// it starts to search by using the explore goal to move to random map locations
				if (lrp2D.IsZero() || owner->IsAtPosition(lrp2D))
				{
					OutputDebugString(L"bot reached lrp and hasn't found target, hunting: GoalExplore.  \n");
					AddSubgoal(new GoalExplore(owner));
				}
				else
				{
					OutputDebugString(L"Active target, hunting : GoalMoveToPosition.  \n");
					AddSubgoal(new GoalMoveToPosition(owner, lrp));
				}
			}
			else
			{
				OutputDebugString(L"No active target, completed hunting.");
				// if there is no active target then this goal can be removed from queue
				status = Completed;
			}
		}

		int GoalHuntTarget::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);

			status = ProcessSubgoals(args);

			// if target is in view, this goal is satisfied
			if (owner->GetTargetSys()->IsTargetWithinFOV())
			{
				OutputDebugString(L"Target Within FOV, completed hunting.");
				status = Completed;
			}

			return status;
		}
		

		void GoalHuntTarget::Draw(const DrawArgs& args)
		{
			// show last recorded position if present
			if (owner->GetTargetSys()->IsTargetPresent())
			{
				Vector3 lrp = owner->GetTargetSys()->GetLastRecordedPosition();

				Vector3 start = lrp - Vector3(1.0f, 0, 0) + Vector3(0, 0, 1.0f);
				Vector3 end =	lrp + Vector3(1.0f, 0, 0) - Vector3(0, 0, 1.0f);
				args.Graphics->DrawLine(start, end, Color(1, 1, 1, 1));

				start = lrp - Vector3(1.0f, 0, 0) - Vector3(0, 0, 1.0f);
				end =	lrp + Vector3(1.0f, 0, 0) + Vector3(0, 0, 1.0f);
				args.Graphics->DrawLine(start, end, Color(1, 1, 1, 1));
			}

			GoalComposite<TikiBot>::Draw(args);
		}

	}
}