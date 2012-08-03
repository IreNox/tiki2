#pragma once

#include "Core/IRigidBody.h"
#include "PhysX/Physics/NxPhysics.h"
//#include "Core/Vector3.h"

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

			void SetMass(Single mass);
			Single GetMass();

			void SetVelocity(const Vector3& linearVelocity);
			Vector3 GetVelocity();

			void SetAngularVelocity(const Vector3& angularVelocity);
			Vector3 GetAngularVelocity();


		private:
			NxBodyDesc bodyDescription;
			NxActor* actor;

			Single mass;
			Vector3 velocity;
			Vector3 angularVelocity;
		};

	}
}