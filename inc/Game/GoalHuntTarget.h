#pragma once

#include "Game/GoalComposite.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		class GoalHuntTarget : public GoalComposite<TikiBot>
		{
		public:
			GoalHuntTarget(TikiBot* bot);

			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate() { }
			void Draw(const DrawArgs& args);

		private:
			// this value is set to true if the last visible position 
			// of the target bot has been searched without success.
			bool lvpTried;
		};

	}
}