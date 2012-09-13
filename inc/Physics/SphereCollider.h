#pragma once

#include "Physics/Collider.h"
#include "Core/ISphereCollider.h"

namespace TikiEngine 
{
	namespace Physics
	{
		using namespace TikiEngine::Components;

		class SphereCollider : public Collider, public ISphereCollider 
		{
		public:
			/*! @brief Create BoxCollider */
			SphereCollider(Engine* engine, GameObject* gameObject);

			/*! @brief Destructor */
			~SphereCollider();
			
			// ICollider Methods
			IRigidBody* GetRigidBody();
			void SetMaterial(int index);

			Vector3 GetCenter();
			void SetCenter(const Vector3& center);

			bool GetDynamic();
			void SetDynamic(bool dynamicFlag);

			bool GetTrigger();
			void SetTrigger(bool triggerFlag);

			void SetGroup(CollisionGroups group);


			// ISphereCollider
			Single GetRadius();
			void SetRadius(Single radius);

			// Component
			bool GetReady();
			void Update(const UpdateArgs& args);
			void Draw(const DrawArgs& args) {}

		private:
			/*! @brief (re)Initialize SphereCollider */
			void UpdateData();

		private:
			Single radius;

		};

	}
}