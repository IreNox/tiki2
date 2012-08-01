#pragma once

#include "GameObject.h"

namespace TikiEngine
{
	namespace Components
	{
		/*! @brief An Interface of all colliders. */
		class ICollider : public Component
		{
		public:

			/*! @brief Create Collider Component */
			ICollider(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject, CT_Collider)
			{
			}
			~ICollider() {}

		};
	}
}