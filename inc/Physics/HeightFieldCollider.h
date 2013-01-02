#pragma once

#include "Core/IHeightFieldCollider.h"
#include "Physics/Collider.h"

namespace TikiEngine
{
	namespace Physics
	{
		using namespace TikiEngine::Components;

		class HeightFieldCollider : public IHeightFieldCollider, public Collider
		{
		public:

			HeightFieldCollider(Engine* engine, GameObject* gameObject);
			~HeightFieldCollider();

			void SetGroup(CollisionGroups group) { Collider::SetCollisionGroup(group); }
			
			IPhysicsMaterial* GetMaterial() { return getInternMaterial(); }
			void SetMaterial(IPhysicsMaterial* mat) { setInternMaterial(mat); }

			Vector3 GetCenter() { return Collider::GetCenterPos(); }
			void SetCenter(const Vector3& center) { Collider::SetCenterPos(center); }

			bool GetDynamic() { return Collider::GetDynamicFlag(); }
			void SetDynamic(bool dynamicFlag) { Collider::SetDynamicFlag(dynamicFlag); }

			bool GetTrigger() { return Collider::GetTriggerFlag(); }
			void SetTrigger(bool triggerFlag) { Collider::SetTriggerFlag(triggerFlag); }

			IRigidBody* GetRigidBody() { return Collider::GetBody(); }

			void SetHeightField(UInt16* height, const HeightFieldDesc& desc);

			void Draw(const DrawArgs& args) {}
			void Update(const UpdateArgs& args) {}

			bool GetReady() { return heightField != 0; }

		private:

			NxHeightField* heightField;

		};
	}
}