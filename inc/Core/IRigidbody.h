#pragma once

#include "Core/Object.h"
#include "Vector3.h"

namespace TikiEngine
{
	namespace Components
	{
		class IRigidBody : public Object
		{
		public: 
			IRigidBody()
				: Object()
			{
			}

			virtual ~IRigidBody() {}

			virtual void SetMass(Single mass) = 0;
			virtual Single GetMass() = 0;

			virtual void SetVelocity(const Vector3& linearVelocity) = 0;
			virtual Vector3 GetVelocity() = 0;

			virtual void SetAngularVelocity(const Vector3& angularVelocity) = 0;
			virtual Vector3 GetAngularVelocity() = 0;

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