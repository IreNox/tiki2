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

        protected:
            // process any subgoals that may be present
            int ProcessSubgoals();

            // passes the message to the front-most subgoal
            bool ForwardMessageToFrontMostSubgoal(const Telegram& msg);

            // composite goals may have any number of subGoals
            SubgoalList subGoals;
        };


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


    }
}
