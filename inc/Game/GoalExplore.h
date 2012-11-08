#pragma once

#include "Game/GoalComposite.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		class GoalExplore : public GoalComposite<TikiBot>
		{

		public:
			GoalExplore(TikiBot* bot);

			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate() { }

		private:
			Vector3 currentDestination;

			// set to true when the destination for the exploration has been established
			bool destinationIsSet;
		};


	}
}