#pragma once

#include "Physics/RigidBody.h"
#include "Physics/PhysicsMaterial.h"


namespace TikiEngine 
{
	namespace Physics
	{
		class Collider
		{
		public: 
			Collider();
			virtual ~Collider() {}

			// These Methods can be used at runtime to raise Trigger flags
			bool GetTriggerFlag();
			void SetTriggerFlag(bool triggerFlag);

			bool GetKinematicFlag();
			void SetKinematicFlag(bool kinematicFlag);


			RigidBody GetRigidBody() { return rigidBody;}

		protected:
			bool isTrigger;
			bool isKinematic;	// check if we have rigid body
			bool isDynamic;
			RigidBody rigidBody;
			NxActor* actor;
			NxActorDesc actorDescription;
			PhysicsMaterial material;
		};
	}
}