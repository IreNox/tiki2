#pragma once

#include "Game/GoalComposite.h"
#include "Game/PathEdge.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		class GoalFollowPath : public GoalComposite<TikiBot>
		{

		public:
			GoalFollowPath(TikiBot* bot, std::list<PathEdge> pathList);

			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate() {}
			void Draw(const DrawArgs& args);

		private:
			// a local copy of the path returned by the path planner
			std::list<PathEdge> path;
		};


	}
}