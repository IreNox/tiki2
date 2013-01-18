#include "Game/TikiSteering.h"
#include "Game/TikiBot.h"
#include "Game/SceneLevel.h"
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace AI
	{
		TikiSteering::TikiSteering(TikiBot* agent) :
			tikiBot(agent),
			flags(0),
			weightSeparation(2.0f),
			weightWander(1.0f),
			weightWallAvoidance(10.0),
			viewDistance(10.0f),
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
			float theta = RandFloat() * TwoPi;

			//create a vector to a target position on the wander circle
			wanderTarget = Vector2(wanderRadius * cosf(theta),
	   						       wanderRadius * sinf(theta));

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
			Vector2 force = Vector2::Zero;

 			if (On(separation))
 			{
 				force = Separation() * weightSeparation;
 
 				if (!AccumulateForce(steeringForce, force))
 					return steeringForce;
 			}

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

			if (On(wander))
			{
				force = Wander() * weightWander;

				if (!AccumulateForce(steeringForce, force)) 
					return steeringForce;
			}


			return steeringForce;
		}

		// calculates a force repelling from the other neighbors
		Vector2 TikiSteering::Separation()
		{
			Vector2 separationForce = Vector2::Zero;

			tikiBot->GetGameState()->GetScene()->SceneGraph.DoWithinRange(tikiBot->Pos3D(), tikiBot->BRadius() + 1, [&](GameObject* go) 
			{ 

 				if (go != 0)
 				{
 					TikiBot *owner = tikiBot;
 
 					TikiBot* bot = 0;
 					bot = go->GetComponent<TikiBot>();
 
 					if (bot != 0 && bot->ID() != owner->ID())
 					{
 						Vector2 toBot = owner->Pos() - bot->Pos();
 
 						// scale the force inversely proportional to the agents distance from its neighbor.
 						separationForce += Vector2::Normalize(toBot) / toBot.Length();
 					}
 				}

			});

			return separationForce;
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
			float dist = ToTarget.Length();

			if (dist > 0)
			{
				//because Deceleration is enumerated as an int, this value is required
				//to provide fine tweaking of the deceleration..
				const float DecelerationTweaker = 0.3f;

				//calculate the speed required to reach the target given the desired deceleration
				float speed =  dist / ((float)decel * DecelerationTweaker);     

				//make sure the velocity does not exceed the max
				speed = MinOf(speed, (float)tikiBot->MaxSpeed());

				//from here proceed just like Seek except we don't need to normalize 
				//the ToTarget vector because we have already gone to the trouble of calculating its length: dist. 
				Vector2 DesiredVelocity =  ToTarget * speed / dist;

				return (DesiredVelocity - tikiBot->Velocity());
			}

			return Vector2::Zero;
		}

		Vector2 TikiSteering::Wander()
		{
			// first, add a small random vector to the target's position
			wanderTarget += Vector2(RandomClamped() * wanderJitter,
									RandomClamped() * wanderJitter);

			// reproject this new vector back on to a unit circle
			wanderTarget.Normalize();

			// increase the length of the vector to the same as the radius of the wander circle
			wanderTarget = wanderTarget * wanderRadius;

			// move the target into a position WanderDist in front of the agent
			Vector2 theTarget = wanderTarget + Vector2(wanderDistance, 0);

			// project the target into world space
			Vector2 projectedTarget = PointToWorldSpace(theTarget, 
														tikiBot->Heading(),
														tikiBot->Side(),
														tikiBot->Pos());
			//and steer towards it
			return projectedTarget - tikiBot->Pos();
		}


		// This function calculates how much of its max steering force the bot has left to apply 
		// and then applies that amount of the force to add.
		bool TikiSteering::AccumulateForce(Vector2 &RunningTot, Vector2 ForceToAdd)
		{
			// calculate how much steering force the bot has used so far
			float MagnitudeSoFar = RunningTot.Length();

			// calculate how much steering force remains to be used by this vehicle
			float MagnitudeRemaining = (float)tikiBot->MaxForce() - MagnitudeSoFar;

			// return false if there is no more force left to use
			if (MagnitudeRemaining <= 0.0f) 
				return false;

			//calculate the magnitude of the force we want to add
			float MagnitudeToAdd = ForceToAdd.Length();
  
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