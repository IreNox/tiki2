#pragma once

#include "Game/GoalComposite.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		class GoalPatrol : public GoalComposite<TikiBot>
		{

		public:
			GoalPatrol(TikiBot* bot, const List<Vector2>& wayPoints);

			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate() {}
			void Draw(const DrawArgs& args);

		private:

			Vector2 currWp;
			List<Vector2> path;
            //double timeWpLeft;
			bool attacking;

		};



	}
}