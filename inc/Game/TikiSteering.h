#pragma once

#include <vector>
#include "Core/Vector2.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiBot;

		//Wander Constants
		//the radius of the constraining circle for the wander behavior
		const float WanderRad    =  20.0f; //1.2f; // 10.0f;
		//distance the wander circle is projected in front of the agent
		const float WanderDist   = 50.0f; //2.0f;
		//the maximum amount of displacement along the circle each frame
		const float WanderJitterPerSec = 40.0f;

		class TikiSteering
		{
		public:
			enum summing_method{weighted_average, prioritized, dithered};

		private:
			enum behavior_type
			{
				none               = 0x00000,
				seek               = 0x00002,
				arrive             = 0x00008,
				wander             = 0x00010,
				separation         = 0x00040,
				wall_avoidance     = 0x00200,
			};

			// Arrive makes use of these to determine how quickly a TikiBot should decelerate to its target
			enum Deceleration{slow = 3, normal = 2, fast = 1};

			// Default 
			Deceleration deceleration;

		public:
			TikiSteering(TikiBot* agent);
			virtual ~TikiSteering() {}

			// calculates and sums the steering forces from any active behaviors
			Vector2 Calculate();

			// Set and Get Target
			void SetTarget(Vector2 t) { target = t; }
			Vector2 Target() const { return target; }
			
			Vector2 Force() const { return steeringForce; }

			// Set and Get Bahvior Flags
			void SeekOn()   { flags |= seek;   }
			void ArriveOn() { flags |= arrive; }
			void WanderOn() { flags |= wander; }

			void SeekOff()   { if(On(seek))   flags ^=seek;   }
			void ArriveOff() { if(On(arrive)) flags ^=arrive; }
			void WanderOff() { if(On(wander)) flags ^=wander; }

			bool SeekIsOn()	  { return On(seek);   }
			bool ArriveIsOn() { return On(arrive); }
			bool WanderIsOn() { return On(wander); }

		private:
			//this function tests if a specific bit of m_iFlags is set
			bool On(behavior_type bt) {return (flags & bt) == bt;}

			bool AccumulateForce(Vector2 &RunningTot, Vector2 ForceToAdd);

			// calculates and sums the steering forces from any active behaviors
			Vector2 CalculatePrioritized();

			// this behavior moves the agent towards a target position
			Vector2 Seek(const Vector2& targetPos);

			// this behavior is similar to seek but it attempts to arrive at the target with a zero velocity
			Vector2 Arrive(const Vector2& targetPos, const Deceleration deceleration);

			// this behavior makes the agent wander about randomly
			Vector2 Wander();



		private:
			// a pointer to the owner of this instance
			TikiBot* tikiBot;

			//the steering force created by the combined effect of all the selected behaviors
			Vector2 steeringForce;

			// these can be used to keep track of friends, pursuers, or prey
			TikiBot* targetAgent1;
			TikiBot* targetAgent2;

			// the current target
			Vector2 target;



			// the current position on the wander circle the agent is attempting to steer towards
			Vector2 wanderTarget; 

			// explained above
			float wanderJitter;
			float wanderRadius;
			float wanderDistance;


			// multipliers. These can be adjusted to effect strength of the appropriate behavior.
			double weightSeparation;
			float weightWander;
			double weightWallAvoidance;
			float weightSeek;
			float weightArrive;


			// how far the agent can "see"
			double viewDistance;

			// binary flags to indicate whether or not a behavior should be active
			int flags;

  


			// is cell space partitioning to be used or not?
			bool          cellSpaceOn;
 
			// what type of method is used to sum any active behavior
			summing_method  summingMethod;



		};


	}
}