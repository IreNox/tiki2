#pragma once

#include "Core/DrawArgs.h"

namespace TikiEngine
{
    namespace AI
    {
        struct Telegram;

        template <class entity_type>
        class Goal
        {
        public: 
            enum 
            {
                // The goal has been activated and will be processed each update step
                Active,
                // The goal is waiting to be activated.
                Inactive,
                // The goal has completed and will be removed on the next Update
                Completed,
                // The goal has failed and will either replan or be removed on the next update
                Failed
            };

        public:
            Goal(entity_type* ent, int type)
            {
                goalType = type;
                owner = ent;
                status = Inactive;
            }

            virtual ~Goal() {}

            // logic to run when the goal is activated.
            virtual void Activate() = 0;

            // logic to run each update-step
            virtual int Process() = 0;

            // logic to run when the goal is satisfied. (typically used to switch off any active steering behaviors)
            virtual void Terminate() = 0;

            // goals can handle messages. Many don't though, so this defines a default behavior
            virtual bool HandleMessage(const Telegram& msg) { return false; }

            // a Goal is atomic and cannot aggregate subgoals yet we must implement this method to provide 
            // the uniform interface required for the goal hierarchy.
            virtual void AddSubgoal(Goal<entity_type>* g)
            {
                throw std::runtime_error("Cannot add goals to atomic goals");
            }

            //used to render any goal specific information
            virtual void Draw(const DrawArgs& args) { }

            // Goal status Getters
            bool IsComplete() const { return status == Completed; }
            bool IsActive()   const { return status == Active;    }
            bool IsInactive() const { return status == Inactive;  }
            bool HasFailed()  const { return status == Failed;    }
			int  GetType()	  const { return goalType; }

        protected:
            //if status = inactive this method sets it to active and calls Activate()
            void ActivateIfInactive();

            // if status is failed this method sets it to inactive so that the goal will be reactivated (+ re-planned) on next update.
            void ReactivateIfFailed();


        protected:
            // an enumarated value indicating the goals's status (see above)
            int status;

            // an enumerated type specifying the type of goal
            int goalType;

            // a pointer to the entity that owns this goal
            entity_type* owner;
        };

        template <class entity_type>
        void Goal<entity_type>::ReactivateIfFailed()
        {
            if (HasFailed())
                status = Inactive;
        }

        template <class entity_type>
        void Goal<entity_type>::ActivateIfInactive()
        {
            if (IsInactive())
                Activate();
        }

    }
}