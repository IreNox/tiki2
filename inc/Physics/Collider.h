#pragma once

#include "Physics/RigidBody.h"
#include "Physics/PhysicsMaterial.h"


namespace TikiEngine 
{
	namespace Physics
	{
		enum ColliderState
		{
			CS_UNINITIALIZED,
			CS_STATIC,
			CS_DYNAMIC
		};

		class Collider
		{
		public: 
			Collider();
			virtual ~Collider() {}

			void SetMaterialIndex(int index);

			bool GetDynamicFlag();
			void SetDynamicFlag(bool dynamicFlag);

			// These Methods can be used at runtime to raise Trigger flags
			bool GetTriggerFlag();
			void SetTriggerFlag(bool triggerFlag);

			bool GetKinematicFlag();
			void SetKinematicFlag(bool kinematicFlag);

		

			RigidBody GetRigidBody() { return rigidBody;}

		protected:
			ColliderState state;
			bool isTrigger;
			bool isKinematic;	// check if we have rigid body
			RigidBody rigidBody;
			NxActor* actor;
			NxActorDesc actorDescription;
			int materialIndex;
			
		};
	}
}