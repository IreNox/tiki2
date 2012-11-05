#pragma once

#include "Game/Goal.h"
#include "Game/PathEdge.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
    namespace AI
    {
		// This directs a bot along a path edge and continuously monitors its progress
		// to ensure it doesn’t get stuck.
		class GoalTraverseEdge : public Goal<TikiBot>
		{

		public:
			GoalTraverseEdge(TikiBot* bot, PathEdge pathEdge, bool lastEdge);

			void Activate(const UpdateArgs& args);
			int Process(const UpdateArgs& args);
			void Terminate();
			void Draw(const DrawArgs& args);


		private:
			// returns true if the bot gets stuck
			bool IsStuck() const;

			// the edge the bot will follow
			PathEdge edge;

			// true if edge is the last in the path.
			bool lastEdgeInPath;

			// the estimated time the bot should take to traverse the edge
			double timeExpected;

			// this records the time this goal was activated
			double startTime;

		};

	}
}