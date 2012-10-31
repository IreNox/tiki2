#pragma once

#include "Game/GoalComposite.h"
#include "Game/TikiBot.h"


namespace TikiEngine
{
	namespace AI
	{

		class GoalThink : public GoalComposite<TikiBot>
		{


		public:
			GoalThink(TikiBot* bot);
			~GoalThink();


			#pragma region GoalComposite 
			void Activate();
			int Process();
			void Terminate() { }

			void Draw(const DrawArgs& args);
			#pragma endregion

			// returns true if the given goal is not at the front of the subgoal list
			bool NotPresent(unsigned int gt) const;

			// top/low level goal types
			void AddGoalWander();
			void AddGoalSeek(Vector2 pos);


		};
	}
}