#include "Game/TikiSteering.h"

namespace TikiEngine
{
	namespace AI
	{
		TikiSteering::TikiSteering(TikiBot* agent) :
			tikiBot(agent),
			flags(0),
			weightSeparation(10.0),
			weightWander(1.0),
			weightWallAvoidance(10.0),
			viewDistance(15.0),
			wallDetectionFeelerLength(25.0), // * bot scale
			feelers(3),
			deceleration(normal),
			targetAgent1(0),
			targetAgent2(0),
			wanderDistance(WanderDist),
			wanderJitter(WanderJitterPerSec),
			wanderRadius(WanderRad),
			weightSeek(0.5f),
			weightArrive(1.0f),
			cellSpaceOn(false),
			summingMethod(prioritized)
		{
			//stuff for the wander behavior
			double theta = RandFloat() * TwoPi;

			//create a vector to a target position on the wander circle
			wanderTarget = Vector2((float)(wanderRadius * cos(theta)),
	   						       (float)(wanderRadius * sin(theta)));

		}

		Vector2 TikiSteering::Calculate()
		{
			// reset the steering force
			steeringForce = Vector2::Zero;

			steeringForce = CalculatePrioritized();

			return steeringForce;
		}

		Vector2 TikiSteering::CalculatePrioritized()
		{
			Vector2 force;

			if(On(seek))
			{
				force = Seek(target) * weightSeek;

				if (!AccumulateForce(steeringForce, force)) 
					return steeringForce;
			}

			if (On(arrive))
			{
				force = Arrive(target, deceleration) * weightArrive;

				if (!AccumulateForce(steeringForce, force)) 
					return steeringForce;
			}

			return steeringForce;
		}

		// Given a target, this behavior returns a steering force which will direct the agent towards the target
		Vector2 TikiSteering::Seek(const Vector2& targetPos)
		{
			Vector2 desiredVelocity = Vector2::Normalize(targetPos - tikiBot->Pos())
									   * (float)tikiBot->MaxSpeed();
			return (desiredVelocity - tikiBot->Velocity());
		}

		Vector2 TikiSteering::Arrive(const Vector2& targetPos, const Deceleration decel)
		{
			Vector2 ToTarget = targetPos - tikiBot->Pos();

			//calculate the distance to the target
			double dist = ToTarget.Length();

			if (dist > 0)
			{
				//because Deceleration is enumerated as an int, this value is required
				//to provide fine tweaking of the deceleration..
				const double DecelerationTweaker = 0.3;

				//calculate the speed required to reach the target given the desired
				//deceleration
				double speed =  dist / ((double)decel * DecelerationTweaker);     

				//make sure the velocity does not exceed the max
				speed = MinOf(speed, tikiBot->MaxSpeed());

				//from here proceed just like Seek except we don't need to normalize 
				//the ToTarget vector because we have already gone to the trouble
				//of calculating its length: dist. 
				Vector2 DesiredVelocity =  ToTarget * (float)(speed / dist);

				return (DesiredVelocity - tikiBot->Velocity());
			}

			return Vector2::Zero;
		}


		// This function calculates how much of its max steering force the bot has left to apply 
		// and then applies that amount of the force to add.
		bool TikiSteering::AccumulateForce(Vector2 &RunningTot, Vector2 ForceToAdd)
		{
			// calculate how much steering force the vehicle has used so far
			double MagnitudeSoFar = RunningTot.Length();

			// calculate how much steering force remains to be used by this vehicle
			double MagnitudeRemaining = tikiBot->MaxForce() - MagnitudeSoFar;

			// return false if there is no more force left to use
			if (MagnitudeRemaining <= 0.0) 
				return false;

			//calculate the magnitude of the force we want to add
			double MagnitudeToAdd = ForceToAdd.Length();
  
			// if the magnitude of the sum of ForceToAdd and the running total
			// does not exceed the maximum force available to this bot, just
			// add together. Otherwise add as much of the ForceToAdd vector is
			// possible without going over the max.
			if (MagnitudeToAdd < MagnitudeRemaining)
			{
				RunningTot += ForceToAdd;
			}
			else
			{
				MagnitudeToAdd = MagnitudeRemaining;

				// add it to the steering force
				RunningTot += (Vector2::Normalize(ForceToAdd) * (float)MagnitudeToAdd); 
			}

			return true;
		}


	}
}