#pragma once

#include "Physics/Collider.h"
#include "Core/IBoxCollider.h"



namespace TikiEngine 
{
	namespace Physics
	{
		using namespace TikiEngine::Components;

		class BoxCollider : public Collider, public IBoxCollider 
		{
		public:
			/*! @brief Create BoxCollider 
			 *  @param setCenter The center of the box, measured in the object's local space.
			 *  @param setSize The size of the box, measured in the object's local space.
			*/
			BoxCollider(Engine* engine, GameObject* gameObject);

			/*! @brief Destructor */
			~BoxCollider();
			
			// ICollider Methods
			void SetMaterial(int index);

			bool GetDynamic();
			void SetDynamic(bool dynamicFlag);

			bool GetTrigger();
			void SetTrigger(bool triggerFlag);

			bool GetKinematic();
			void SetKinematic(bool kinematicFlag);


			// IBoxCollider
			Vector3 GetCenter();
			void SetCenter(const Vector3& center);

			Vector3 GetSize();
			void SetSize(const Vector3& size);

			bool GetReady();

			void Update(const UpdateArgs& args) {}
			void Draw(const DrawArgs& args) {}

		private:
			/*! @brief (re)Initialize BoxCollider */
			void UpdateData();

		private:
			NxVec3 center;
			NxVec3 size;

		};

	}
}