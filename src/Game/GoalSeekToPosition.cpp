#include "Game/GoalSeekToPosition.h"

#include "Game/GoalTypes.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace AI
	{
		GoalSeekToPosition::GoalSeekToPosition(TikiBot* bot, Vector2 target)
			: Goal<TikiBot>(bot, Goal_Seek_To_Position)
		{
			position = target;
			timeToReachPos = 0.0;
		}


		void GoalSeekToPosition::Activate()
		{
			status = Active;

			// TODO: 
			//startTime =  get current time
			//timeToReachPos = owner->CalculateTimeToReachPosition(position);
			//const double MarginOfError = 1.0;
			//timeToReachPos += MarginOfError;

			// set target and start seeking
			owner->GetSteering()->SetTarget(position);
			owner->GetSteering()->SeekOn();
		}

		int GoalSeekToPosition::Process()
		{
			// if status is inactive, call Activate
			ActivateIfInactive();

			// TODO: 
			if (IsStuck())
				status = Failed;
			else
			{
				if (owner->IsAtPosition(position))
					status = Completed;
			}

			return status;
		}

		void GoalSeekToPosition::Terminate()
		{
			owner->GetSteering()->SeekOff();
			owner->GetSteering()->ArriveOff();

			status = Completed;
		}

		void GoalSeekToPosition::Draw(const DrawArgs& args)
		{
			Vector3 seekPos = Vector3(position.X, owner->Pos3D().Y, position.Y);
			args.Graphics->DrawLine(owner->Pos3D(), seekPos, Color::Red);	
		}

		bool GoalSeekToPosition::IsStuck() const
		{
			// TODO
			return false;
		}


	}
}