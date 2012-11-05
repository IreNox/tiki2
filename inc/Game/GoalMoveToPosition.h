#pragma once

#include "Game/GoalComposite.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{

		class GoalMoveToPosition : public GoalComposite<TikiBot>
		{

		public:
			GoalMoveToPosition(TikiBot* bot, Vector3 dest);
			
			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate() {}
			void Draw(const DrawArgs& args);

		private:
			Vector3 destination;
		};

	}
}