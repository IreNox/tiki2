#pragma once

#include "Core/Component.h"

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
			virtual ~ICollider() {}

			 /*! @brief OnTriggerEnter is called when the Collider other enters the trigger. */
			 //virtual void OnTriggerEnter(ICollider* other) = 0;

			 /*! @brief OnTriggerExit is called when the Collider other has stopped touching the trigger. */
			 //virtual void OnTriggerExit(ICollider* other) = 0;

			 /*! @brief OnTriggerStay is called almost all the frames for every Collider other that is touching the trigger. */
			 //virtual void OnTriggerStay(ICollider* other) = 0;

			 /*! @brief Is the collider a trigger? */
			 // virtual bool IsTrigger() = 0;
			 
			 /*! @brief Sets whether the collider is a trigger */
			 //virtual void SetTrigger(bool isTrigger) = 0;

		};
	}
}