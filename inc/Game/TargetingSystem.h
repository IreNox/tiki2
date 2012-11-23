#pragma once

#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiBot;

		class TargetingSystem
		{
		public:
			TargetingSystem(TikiBot* owner);

			// each time this method is called the opponents in the owner's sensory 
			// memory are examined and the closest  is assigned to currentTarget.
			// if there are no opponents that have had their memory records updated
			// within the memory span of the owner then the current target is set to null
			void Update(const UpdateArgs& args);

			// returns true if there is a currently assigned target
			bool IsTargetPresent() const { return currentTarget != 0; }

			// returns true if the target is within the field of view of the owner
			bool IsTargetWithinFOV() const;

			// returns true if there is unobstructed line of sight between the target and the owner
			bool IsTargetShootable() const;

			// returns the position the target was last seen. Throws an exception if there is no target currently assigned
			Vector3 GetLastRecordedPosition() const;

			// returns the amount of time the target has been in the field of view
			double GetTimeTargetHasBeenVisible(const UpdateArgs& args) const;

			// returns the amount of time the target has been out of view
			double GetTimeTargetHasBeenOutOfView(const UpdateArgs& args) const;

			// returns a pointer to the target. null if no target current.
			TikiBot* GetTarget() const { return currentTarget; }

			// sets the target pointer to null
			void ClearTarget() { currentTarget = 0; }

			// sets the global target pointer to null
			void ClearGlobalTarget() { globalTarget = 0; /*currentTarget = 0;*/ }

			// sets a user defined global target
			void SetGlobalTarget(TikiBot* target) { globalTarget = target; }

		private:
			// The owner of this system
			TikiBot* owner;

			// The current target (this will be null if there is no target assigned)
			TikiBot* currentTarget;

			// The global target set by some user.
			TikiBot* globalTarget;

		};

	}
}