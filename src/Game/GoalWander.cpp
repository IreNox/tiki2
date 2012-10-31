#include "Game/GoalWander.h"

#include "Game/GoalTypes.h"

namespace TikiEngine
{
	namespace AI
	{
		GoalWander::GoalWander(TikiBot* bot)
			: Goal<TikiBot>(bot, Goal_Wander)
		{

		}

		void GoalWander::Activate()
		{
			status = Active;
			owner->GetSteering()->WanderOn();
		}

		int GoalWander::Process()
		{
			// if status is inactive, call Activate()
			ActivateIfInactive();
			return status;
		}

		void GoalWander::Terminate()
		{
			owner->GetSteering()->WanderOff();
		}


	}
}