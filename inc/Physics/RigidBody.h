#pragma once

#include "Core/IRigidBody.h"
#include "PhysX/Physics/NxPhysics.h"


namespace TikiEngine 
{
	namespace Physics
	{
		using namespace TikiEngine::Components;

		class RigidBody : public IRigidBody
		{
		public:
			RigidBody();
			~RigidBody();

			
			NxBodyDesc* GetDescription();
			void SetActor(NxActor* setActor);

			void SetKinematic(bool kinematicFlag);
			bool GetKinematic();

			void SetMass(Single mass);
			Single GetMass();

			void SetVelocity(const Vector3& linearVelocity);
			Vector3 GetVelocity();

			void SetAngularVelocity(const Vector3& angularVelocity);
			Vector3 GetAngularVelocity();
			
			void MovePosition(const Vector3& pos);
			void MoveRotation(const Quaternion& quat);

		private:
			NxBodyDesc bodyDescription;
			NxActor* actor;

			bool isKinematic;

			Single mass;
			Vector3 velocity;
			Vector3 angularVelocity;
		};

	}
}