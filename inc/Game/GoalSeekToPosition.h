#pragma once

#include "Game/Goal.h"
#include "Game/TikiBot.h"


namespace TikiEngine
{
	namespace AI
	{
		class GoalSeekToPosition : public Goal<TikiBot>
		{

		public:
			GoalSeekToPosition(TikiBot* bot, Vector2 target);

			void Activate();
			int Process();
			void Terminate();

			void Draw(const DrawArgs& args);


		private:
			//TODO: returns true if a bot gets stuck
			bool IsStuck() const;

			// the position the bot is moving to
			Vector2 position;

			// the approximate time the bot should take to travel the target location
			double timeToReachPos;

			// this records the time this goal was activated
			double startTime;


		};


	}
}