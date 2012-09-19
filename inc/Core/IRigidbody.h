#pragma once

#include "Core/TikiObject.h"
#include "Core/Quaternion.h" //includes "Core/Vector3.h"

namespace TikiEngine
{
	namespace Components
	{
		class IRigidBody : public TikiObject
		{
		public: 
			IRigidBody()
				: TikiObject()
			{
			}

			virtual ~IRigidBody() {}

			/*Sets the mass. keep it close to 0.1 and never more than 10. Large masses make physics simulation unstable. */
			virtual void SetMass(Single mass) = 0;
			virtual Single GetMass() = 0;

			virtual void SetVelocity(const Vector3& linearVelocity) = 0;
			virtual Vector3 GetVelocity() = 0;

			virtual void SetAngularVelocity(const Vector3& angularVelocity) = 0;
			virtual Vector3 GetAngularVelocity() = 0;

			/* !@brief Set if this actor should be kinematic. The Collider must be dynamic if this is set to true! */
			virtual void SetKinematic(bool kinematicFlag) = 0;
			virtual bool GetKinematic() = 0;

			/* !@brief Moves a Kinematic-only actor in World Space. */
			virtual void MovePosition(const Vector3& pos) = 0;
			
			/* !@brief Rotates a Kinematic-only actor in World Space. */
			virtual void MoveRotation(const Quaternion& quat) = 0;

			//virtual void SetUseGravity(bool useGravity) = 0;
			//virtual bool UseGravity() = 0;


			// Interpolate Mode

			// Collision Detection Mode

			// Constraints
			//virtual void SetFreezePosition(const Vector3& freezePos);
			//virtual Vector3 GetFreezePosition();

			//virtual void SetFreezeRotation(const Vector3& freezeRot);
			//virtual Vector3 GetFreezeRotation();

		};
	}
}