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
			GoalPatrol(TikiBot* bot, std::list<Vector2> wayPoints);

			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate() {}
			void Draw(const DrawArgs& args);

		private:
			std::list<Vector2> path;
			Vector2 currWp;
            double timeWpLeft;
			bool attacking;

		};



	}
}