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
			virtual ~Collider();

			// TODO: is this the right way to downcast?
			IRigidBody* GetBody() { return rigidBody; }

		protected:
			void SetMaterialIndex(int index);

			Vector3 GetCenterPos();
			void SetCenterPos(const Vector3& center);

			bool GetDynamicFlag();
			void SetDynamicFlag(bool dynamicFlag);

			// These Methods can be used at runtime to raise Trigger or kinematic flags
			bool GetTriggerFlag();
			void SetTriggerFlag(bool triggerFlag);

			void SetCollisionGroup(unsigned short group);


			bool GetReady();

		protected:
			ColliderState state;
			bool isTrigger;
			RigidBody* rigidBody;
			NxActor* actor;
			NxActorDesc actorDescription;
			int materialIndex;
			
			NxVec3 center;
		};
	}
}