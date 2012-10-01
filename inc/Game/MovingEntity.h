#pragma once

#include "Game/BaseGameEntity.h"

namespace TikiEngine
{
	namespace AI
	{
		class MovingEntity : public BaseGameEntity
		{

		public:
			MovingEntity(Engine* engine, GameObject* gameObject);

			virtual ~MovingEntity(){}

			void Init(Double radius = 1, Vector2 velocity = Vector2::Zero, Double maxSpeed = 1.0, 
					  Vector2 heading = Vector2::Zero, Double turnRate = 0.2, Double maxForce = 1.0);

			// accessors
			Vector2 Velocity() const { return velocity; }
			void SetVelocity(const Vector2& newVel) { velocity = newVel; }
  
			Double Mass() const { return mass; }
  
			Vector2 Side() const { return side; }

			Double MaxSpeed() const { return maxSpeed; }                       
			void SetMaxSpeed(Double newSpeed) { maxSpeed = newSpeed; }
  
			double MaxForce() const { return maxForce; }
			void SetMaxForce(Double mf) { maxForce = mf; }

			Boolean IsSpeedMaxedOut() const { return maxSpeed * maxSpeed >= velocity.LengthSquared(); }
			Double Speed() const { return velocity.Length(); }
			Double SpeedSq() const { return velocity.LengthSquared(); }
  
			Vector2 Heading() const { return heading; }
			void SetHeading(Vector2 newHeading);
			Boolean RotateHeadingToFacePosition(Vector2 target);

			Double MaxTurnRate() const { return maxTurnRate; }
			void SetMaxTurnRate(double val) { maxTurnRate = val; }

		protected:
			Vector2 velocity;
  
			// a normalized vector pointing in the direction the entity is heading. 
			Vector2 heading;
			
			// a vector perpendicular to the heading vector
			Vector2 side; 
			
			Double mass;
  			
			// the maximum speed this entity may travel at.
			Double maxSpeed;
			
			// the maximum force this entity can produce to power itself (think about rockets and thrust)
			Double maxForce;
  			
			// the maximum rate (radians per second) this vehicle can rotate         
			Double maxTurnRate;

		};
	}
}