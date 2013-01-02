#pragma once

#include "Physics/Collider.h"
#include "Core/IBoxCollider.h"

namespace TikiEngine 
{
	namespace Physics
	{
		using namespace TikiEngine::Components;

		class BoxCollider : public IBoxCollider, public Collider
		{
		public:
			/*! @brief Create BoxCollider */
			BoxCollider(Engine* engine, GameObject* gameObject);

			/*! @brief Destructor */
			~BoxCollider();
			
			// ICollider Methods
			IRigidBody* GetRigidBody();

			IPhysicsMaterial* GetMaterial() { return getInternMaterial(); }
			void SetMaterial(IPhysicsMaterial* mat) { setInternMaterial(mat); UpdateData(); }

			Vector3 GetCenter();
			void SetCenter(const Vector3& center);

			bool GetDynamic();
			void SetDynamic(bool dynamicFlag);

			bool GetTrigger();
			void SetTrigger(bool triggerFlag);

			void SetGroup(CollisionGroups group);


			// IBoxCollider
			Vector3 GetSize();
			void SetSize(const Vector3& size);

			// Component
			bool GetReady();
			void Update(const UpdateArgs& args);
			void Draw(const DrawArgs& args) {}

		private:
			/*! @brief (re)Initialize BoxCollider */
			void UpdateData();

		private:
			NxVec3 size;

		};

	}
}