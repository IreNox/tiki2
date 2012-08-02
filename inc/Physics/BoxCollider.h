#pragma once

#include "Core/IBoxCollider.h"
#include "Physics/PhysicsMaterial.h"

namespace TikiEngine 
{

	namespace Physics
	{
		using namespace TikiEngine::Components;

		class BoxCollider : public IBoxCollider
		{
		public:
			/*! @brief Create BoxCollider 
			 *  @param setCenter The center of the box, measured in the object's local space.
			 *  @param setSize The size of the box, measured in the object's local space.
			*/
			BoxCollider(Engine* engine, GameObject* gameObject);

			/*! @brief Destructor */
			~BoxCollider();

			
			void Update(const UpdateArgs& args) {}
			void Draw(const DrawArgs& args) {}

			Vector3 GetCenter();
			Vector3 GetSize();
			
			void SetCenter(const Vector3& center);
			void SetSize(const Vector3& size);
			
			bool GetReady();

		private:
			/*! @brief (re)Initialize BoxCollider */
			void UpdateData();

		private:
			bool isTrigger;
			NxVec3 center;
			NxVec3 size;
			NxActor* actor;
			NxActorDesc actorDescription;
			PhysicsMaterial material;
		};

	}
}