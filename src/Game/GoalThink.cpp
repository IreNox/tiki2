#include "Game/GoalThink.h"

#include "Game/GoalWander.h"
//#include "Game/GoalSeekToPosition.h"
//#include "Game/GoalFollowPath.h"
#include "Game/GoalMoveToPosition.h"
#include "Game/GoalTypes.h"


namespace TikiEngine
{
	namespace AI
	{

		GoalThink::GoalThink(TikiBot* bot)
			: GoalComposite<TikiBot>(bot, Goal_Think)
		{
			// TODO: Evaulators

		}


		GoalThink::~GoalThink()
		{

		}

		#pragma region GoalComposite 

		void GoalThink::Activate(const UpdateArgs& args)
		{
			if (!owner->IsPossessed())
			{
				// TODO: Arbitrate()

			}

			status = Active;
		}

		int GoalThink::Process(const UpdateArgs& args)
		{
			ActivateIfInactive(args);

			int subgoalStatus = ProcessSubgoals(args);

			if (subgoalStatus == Completed || subgoalStatus == Failed)
			{
				if (!owner->IsPossessed())
					status = Inactive;
			}

			return status;
		}


		void GoalThink::Draw(const DrawArgs& args)
		{
			std::list<Goal<TikiBot>*>::iterator curGoal;
			for (curGoal = subGoals.begin(); curGoal != subGoals.end(); ++curGoal)
				(*curGoal)->Draw(args);
		}

		#pragma endregion
	
		bool GoalThink::NotPresent(unsigned int gt) const
		{
			if (!subGoals.empty())
				return subGoals.front()->GetType() != gt;

			return true;
		}
	
		void GoalThink::AddGoalWander()
		{
			//RemoveAllSubgoals();
			AddSubgoal(new GoalWander(owner));
		}


		void GoalThink::AddGoalMoveToPosition(Vector3 pos)
		{
			AddSubgoal( new GoalMoveToPosition(owner, pos));
		}

		void GoalThink::QueueGoalMoveToPosition(Vector3 pos)
		{
			subGoals.push_back(new GoalMoveToPosition(owner, pos));
		}


	}
}