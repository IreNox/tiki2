#include "Game/GoalTraverseEdge.h"

#include "Game/GoalTypes.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace AI
	{
		GoalTraverseEdge::GoalTraverseEdge(TikiBot* bot, PathEdge pathEdge, bool lastEdge)
			: Goal<TikiBot>(bot, Goal_Traverse_Edge), 
			  edge(pathEdge)
		{
			this->lastEdgeInPath = lastEdge;
			timeExpected = 0.0;
		}

		void GoalTraverseEdge::Activate(const UpdateArgs& args)
		{
			status = Active;

			// TODO
			startTime = args.Time.TotalTime;
			//timeExpected = owner->CalcTimeToReachPos(edge.destination);
			//static const double MarginOfError = 2.0;
			//timeExpected += MarginOfError;

			// set target and steer/arrive towards it
			owner->GetSteering()->SetTarget(edge.Destination());

			if (lastEdgeInPath)
				owner->GetSteering()->ArriveOn();
			else
				owner->GetSteering()->SeekOn();
		}

		int GoalTraverseEdge::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);

			// if the bot has become stuck, return failure
			if (IsStuck())
				status = Failed;
			else
			{
				// if the bot has reached the end of the edge return completed
				if (owner->IsAtPosition(edge.Destination()))
					status = Completed;
			}

			return status;
		}

		void GoalTraverseEdge::Terminate()
		{
			// turn off steering behaviors.
			owner->GetSteering()->SeekOff();
			owner->GetSteering()->ArriveOff();

            if( owner->GetGameObject()->GModel())
            {
                if (lastEdgeInPath)
                    owner->GetGameObject()->GModel()->animationEvent->RaiseEvent(owner->GetGameObject()->GModel(), AnimationArgs(Idle));
            }

		}

		void GoalTraverseEdge::Draw(const DrawArgs& args)
		{
#if _DEBUG
			Vector3 seekPos = Vector3(edge.Destination().X, owner->Pos3D().Y, edge.Destination().Y);
			args.Graphics->DrawLine(owner->Pos3D(), seekPos, Color::Red);	
#endif
		}



		bool GoalTraverseEdge::IsStuck() const
		{
			// TODO: 
			return false;
		}


	}
}