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

			// TODO: is this the right way to downcast?
			IRigidBody* GetBody() { return &rigidBody;}

		protected:
			void SetMaterialIndex(int index);

			bool GetDynamicFlag();
			void SetDynamicFlag(bool dynamicFlag);

			// These Methods can be used at runtime to raise Trigger or kinematic flags
			bool GetTriggerFlag();
			void SetTriggerFlag(bool triggerFlag);

		protected:
			ColliderState state;
			bool isTrigger;
			RigidBody rigidBody;
			NxActor* actor;
			NxActorDesc actorDescription;
			int materialIndex;
			
		};
	}
}