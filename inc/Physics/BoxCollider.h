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
			
			void Update(const UpdateArgs& args) {}
			void Draw(const DrawArgs& args) {}


			Vector3 GetCenter();
			Vector3 GetSize();
			bool GetDynamic();

			void SetCenter(const Vector3& center);
			void SetSize(const Vector3& size);
			void SetDynamic(bool dynamicFlag);

			bool GetReady();

		private:
			/*! @brief (re)Initialize BoxCollider */
			void UpdateData();

		private:
			NxVec3 center;
			NxVec3 size;

		};

	}
}