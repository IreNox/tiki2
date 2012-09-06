#pragma once

#include "Core/ICollider.h"

namespace TikiEngine
{
	namespace Components
	{
		class ICharacterController : public ICollider
		{
		public:
			ICharacterController(Engine* engine, GameObject* gameObject)
				:ICollider(engine, gameObject) {}
			virtual ~ICharacterController() {}

			/* !@brief 	This will offset the Capsule Collider in world space, and won't affect how the Character pivots. */
			virtual Vector3 GetCenter() = 0;
			virtual void SetCenter(const Vector3& center) = 0;

			/* !@brief 	Length of the Capsule Collider's radius. This is essentially the width of the collider. */
			virtual float GetRadius() = 0;
			virtual void SetRadius(Single radius) = 0; 

			/* !@brief 	The Character's Capsule Collider height. Changing this will scale the collider along the Y axis in both positive and negative directions. */
			virtual float GetHeight() = 0;
			virtual void SetHeight(Single height) = 0; 




		};

	}

}