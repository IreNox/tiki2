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

		void GoalWander::Activate(const UpdateArgs& args)
		{
			status = Active;
			owner->GetSteering()->WanderOn();
		}

		int GoalWander::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);
			return status;
		}

		void GoalWander::Terminate()
		{
			owner->GetSteering()->WanderOff();
		}


	}
}