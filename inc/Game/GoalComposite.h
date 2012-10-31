#pragma once

#include "Game/Goal.h"
#include <list>

namespace TikiEngine
{
    namespace AI
    {
        // Base composite goal class
        template <class entity_type>
        class GoalComposite : public Goal<entity_type>
        {
        private:
            typedef std::list<Goal<entity_type>*> SubgoalList;

        public:
            GoalComposite(entity_type* ent, int type) : 
              Goal(ent, type) {}

            virtual ~GoalComposite() { RemoveAllSubgoals(); }
            
            // logic to run when the goal is activated.
            virtual void Activate() = 0;

            // logic to run each update-step.
            virtual int Process() = 0;

            // logic to run prior to the goal's destruction
            virtual void Terminate() = 0;

            // if a child class of Goal_Composite does not define a message handler the default behavior is 
            // to forward the message to the front-most subgoal
            virtual bool HandleMessage(const Telegram& msg)
            {
                return ForwardMessageToFrontMostSubgoal(msg);
            }

            // adds a subgoal to the front of the subgoal list
            void AddSubgoal(Goal<entity_type>* g);

            // this method iterates through the subgoals and calls each one's Terminate
            // method before deleting the subgoal and removing it from the subgoal list
            void RemoveAllSubgoals();

			virtual void Draw(const DrawArgs& args);

        protected:
			//  this method first removes any completed goals from the front of the
			//  subgoal list. It then processes the next goal in the list (if there is one)
            int ProcessSubgoals();

            // passes the message to the front-most subgoal
            bool ForwardMessageToFrontMostSubgoal(const Telegram& msg);

            // composite goals may have any number of subGoals
            SubgoalList subGoals;
        };

		template <class entity_type>
		void GoalComposite<entity_type>::AddSubgoal(Goal<entity_type>* g)
		{
			subGoals.push_front(g);
		}

        template <class entity_type>
        void GoalComposite<entity_type>::RemoveAllSubgoals()
        {
            for (SubgoalList::iterator it = subGoals.begin(); it != subGoals.end(); ++it)
            {
                (*it)->Terminate();
                delete *it;
            }

            subGoals.clear();
        }


		template <class entity_type>
		int GoalComposite<entity_type>::ProcessSubgoals()
		{
			// remove all completed and failed goals from the front of the subgoal list
			while(!subGoals.empty() && 
				  subGoals.front()->IsComplete() || subGoals.front()->HasFailed())
			{
				subGoals.front()->Terminate();
				delete subGoals.front();
				subGoals.pop_front();
			}

			// if any subgoals remain, process the one at the front of the list
			if (!subGoals.empty())
			{
				// grab the status of the front-most subgoal
				int statusOfSubGoals = subGoals.front()->Process();

				// we have to test for the special case where the front-most subgoal reports 'completed'
				// *and* the subgoal list contains additional goals.When this is the case,
				// to ensure the parent keeps processing its subgoal list we must return the 'active' status.
				if (statusOfSubGoals == Completed && subGoals.size() > 1)
					return Active;

				return statusOfSubGoals;
			}
			else // no more subgoals to process - return 'completed'
				return Completed;

		}



		template <class entity_type>
		bool GoalComposite<entity_type>::ForwardMessageToFrontMostSubgoal(const Telegram& msg)
		{
			// pass the message to the goal at the front of the queue
			if (!subGoals.empty())
				return subGoals.front()->HandleMessage(msg);

			// return false if the message has not been handled
			return false;
		}

		template <class entity_type>
		void GoalComposite<entity_type>::Draw(const DrawArgs& args)
		{
			if (!subGoals.empty())
				subGoals.front()->Draw(args);
		}

    }
}
