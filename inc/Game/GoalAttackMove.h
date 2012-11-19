#pragma once

#include "Game/GoalComposite.h"
#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace AI
	{
		class GoalAttackMove : public GoalComposite<TikiBot>
		{

		public:
			GoalAttackMove(TikiBot* bot, Vector3 dest);

			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate() { }

		private:
			bool attacking;
			Vector3 destination;
		};
	}
}