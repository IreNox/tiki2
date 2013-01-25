#pragma once

#include "Game/BaseGameEntity.h"

namespace TikiEngine
{
	namespace AI
	{
		class MovingEntity : public BaseGameEntity
		{

		public:
			MovingEntity(GameState* gameState, GameObject* gameObject);

			virtual ~MovingEntity(){}

			void Init(Double radius, Vector2 velocity, Double maxSpeed, 
					  Vector2 heading, float turnRate, Double maxForce);

			// accessors
			Vector2 Velocity() const { return velocity; }
			void SetVelocity(const Vector2& TIKI_NEWVel) { velocity = TIKI_NEWVel; }
  
			Double Mass() const { return mass; }
  
			Vector2 Side() const { return side; }

			Double MaxSpeed() const { return maxSpeed; }                       
			void SetMaxSpeed(Double TIKI_NEWSpeed) { maxSpeed = TIKI_NEWSpeed; }
  
			double MaxForce() const { return maxForce; }
			void SetMaxForce(Double mf) { maxForce = mf; }

			bool IsSpeedMaxedOut() const { return maxSpeed * maxSpeed >= velocity.LengthSquared(); }
			Double Speed() const { return velocity.Length(); }
			Double SpeedSq() const { return velocity.LengthSquared(); }
  
			Vector2 Heading() const { return heading; }
			void SetHeading(Vector2 TIKI_NEWHeading);
			bool RotateHeadingToFacePosition(Vector2 target);

			float MaxTurnRate() const { return maxTurnRate; }
			void SetMaxTurnRate(float val) { maxTurnRate = val; }

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
			float maxTurnRate;

		};
	}
}