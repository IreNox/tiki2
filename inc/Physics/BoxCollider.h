#pragma once

#include "Physics/Collider.h"

namespace TikiEngine 
{

	namespace Physics
	{
		using namespace TikiEngine::Components;

		class BoxCollider : public Collider
		{
		public:
			/*! @brief Create BoxCollider 
			 *  @param setCenter The center of the box, measured in the object's local space.
			 *  @param setSize The size of the box, measured in the object's local space.
			*/
			BoxCollider(Engine* engine, GameObject* gameObject, 
						NxVec3 setCenter, NxVec3 setSize, bool setIsTrigger = false);
			
			/*! @brief Destructor */
			~BoxCollider();

			/*! @brief Initialize BoxCollider */
			bool GetReady();
			
			void Draw(const DrawArgs& args) {}
			void Update(const UpdateArgs& args) {}

		private:
			NxVec3 center;
			NxVec3 size;
			
		};

	}
}