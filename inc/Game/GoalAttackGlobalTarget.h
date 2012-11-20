#pragma once

#include "Game/GoalComposite.h"
#include "Game/TikiBot.h"
#include "Game/Regulator.h"


namespace TikiEngine
{
	namespace AI
	{
		class GoalAttackGlobalTarget : public GoalComposite<TikiBot>
		{

		public:
			GoalAttackGlobalTarget(TikiBot* bot, TikiBot* target, Regulator* reg);
			void Activate(const UpdateArgs& args);
			int  Process(const UpdateArgs& args);
			void Terminate();


		private:
			TikiBot* target;
			bool attacking;
			Regulator* attackTargetRegulator;
		};


	}
}