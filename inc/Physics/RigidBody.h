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

			void SetActor(NxActor* setActor);

			void SetMass(Single mass);
			Single GetMass();


		private:
			NxActor* actor;

		};

	}
}