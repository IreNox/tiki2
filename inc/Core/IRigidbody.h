#pragma once

#include "Core/Component.h"

namespace TikiEngine
{
	namespace Components
	{
		class IRigidBody : public Component
		{
		public: 
			IRigidBody(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject, CT_Rigidbody)
			{
			}

			virtual ~IRigidBody() {}

			virtual void SetMass(Single mass) = 0;
			virtual Single GetMass() = 0;

			//virtual void SetDrag(Single drag) = 0;
			//virtual Single GetDrag() = 0;

			//virtual void SetAngularDrag(Single angularDrag) = 0;
			//virtual Single GetAngularDrag() = 0;

			//virtual void SetUseGravity(bool useGravity) = 0;
			//virtual bool UseGravity() = 0;

			//virtual void SetKinematic(bool kinematicFlag) = 0;
			//virtual bool IsKinematic() = 0;

			// INterpolate Mode

			// Collision Detection Mode

			// Constraints
			//virtual void SetFreezePosition(const Vector3& freezePos);
			//virtual Vector3 GetFreezePosition();

			//virtual void SetFreezeRotation(const Vector3& freezeRot);
			//virtual Vector3 GetFreezeRotation();

		};
	}
}