#include "Game/MovingEntity.h"
#include <cassert>

namespace TikiEngine
{
	namespace AI
	{
		MovingEntity::MovingEntity(GameState* gameState, GameObject* gameObject)
			: BaseGameEntity(gameState, gameObject)
		{
		}

		void MovingEntity::Init(Double radius, Vector2 velocity, Double maxSpeed, Vector2 heading, float turnRate, Double maxForce)
		{
			this->heading = heading;
			this->velocity = velocity;
			this->mass = 1;
			this->side = heading.Cross();	
			this->maxSpeed = maxSpeed;
			this->maxTurnRate = turnRate;
			this->maxForce = maxForce;

			// BaseGameEntity
			this->boundingRadius = radius;
		}

		//  first checks that the given heading is not a vector of zero length. If the
		//  TIKI_NEW heading is valid this fumction sets the entity's heading and side vectors accordingly
		void MovingEntity::SetHeading(Vector2 TIKI_NEWHeading)
		{
			assert( (TIKI_NEWHeading.LengthSquared() - 1.0) < 0.00001 );
			this->heading = TIKI_NEWHeading;

			  //the side vector must always be perpendicular to the heading
		    this->side = heading.Cross();
		}

		// TODO: Vector3::Sign() get the signed angle from 2 vectors, 
		// TODO: Matrix::Transform(Vector3)
		// given a target position, this method rotates the entity's heading and
		// side vectors by an amount not greater than m_dMaxTurnRate until it
		// directly faces the target.
		// returns true when the heading is facing in the desired direction
		inline bool MovingEntity::RotateHeadingToFacePosition(Vector2 target)
		{
		 //   Vector2 toTarget = Vector2::Normalize(target - position);
		 //
		 //   //first determine the angle between the heading vector and the target
		 //	  double angle = acos(Vector3::Dot(heading, toTarget));
		 //   
		 //   //return true if the player is facing the target
		 //   if (angle < 0.00001) 
		 //		  return true;
		 //   
		 //   //clamp the amount to turn to the max turn rate
		 //   if (angle > maxTurnRate) 
		 //		  angle = maxTurnRate;
  		 //	    
		 //   //The next few lines use a rotation matrix to rotate the player's heading vector accordingly
		 //   Matrix rotMatrix;
  		 //	    
		 //   //notice how the direction of rotation has to be determined when creating the rotation matrix
		 //	  rotMatrix.Rotate(angle * heading.Sign(toTarget));	
		 //   rotMatrix.Transform(heading);
		 //   rotMatrix.Transform(velocity);
		 //   
		 //   //finally recreate side
		 //   this->side = heading.Perp(); 
		    
		    return false;
		}

	}
}