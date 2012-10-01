#pragma once

#include "BaseGameEntity.h"

namespace TikiEngine
{
	namespace AI
	{
		class MovingEntity : public BaseGameEntity
		{

		public:
			MovingEntity(Engine* engine, GameObject* gameObject);

			virtual ~MovingEntity(){}

			void Init(Double radius = 1, Vector3 velocity = Vector3::Zero, Double maxSpeed = 25.0, Vector3 heading = Vector3::Zero, Double turnRate = 100, Double maxForce = 100);

			// accessors
			Vector3 Velocity() const { return velocity; }
			void SetVelocity(const Vector3& newVel) { velocity = newVel; }
  
			Double Mass() const { return mass; }
  
			Vector3 Side() const { return side; }

			Double MaxSpeed() const { return maxSpeed; }                       
			void SetMaxSpeed(Double newSpeed) { maxSpeed = newSpeed; }
  
			double MaxForce() const { return maxForce; }
			void SetMaxForce(Double mf) { maxForce = mf; }

			Boolean IsSpeedMaxedOut() const { return maxSpeed * maxSpeed >= velocity.LengthSquared(); }
			Double Speed() const { return velocity.Length(); }
			Double SpeedSq() const { return velocity.LengthSquared(); }
  
			Vector3 Heading() const { return heading; }
			void SetHeading(Vector3 newHeading);
			Boolean RotateHeadingToFacePosition(Vector3 target);

			Double MaxTurnRate() const { return maxTurnRate; }
			void SetMaxTurnRate(double val) { maxTurnRate = val; }

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			//virtual void MoveTo(const Vector3& pos) = 0;

		protected:
			Vector3 velocity;
  
			// a normalized vector pointing in the direction the entity is heading. 
			Vector3 heading;
			
			// a vector perpendicular to the heading vector
			Vector3 side; 
			
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