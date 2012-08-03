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

			
			/* !@brief True if this Collider is dynamic, false otherwise */
			virtual bool GetDynamic() = 0;
			/* !@brief Set if the Collider should be dynamicor static */
			virtual void SetDynamic(bool dynamicFlag) = 0;


			 /*! @brief OnTriggerEnter is called when the Collider other enters the trigger. */
			 //virtual void OnTriggerEnter(ICollider* other) = 0;

			 /*! @brief OnTriggerExit is called when the Collider other has stopped touching the trigger. */
			 //virtual void OnTriggerExit(ICollider* other) = 0;

			 /*! @brief OnTriggerStay is called almost all the frames for every Collider other that is touching the trigger. */
			 //virtual void OnTriggerStay(ICollider* other) = 0;

			 /*! @brief Is this collider a trigger? */
			 //virtual bool IsTrigger() = 0;
			 
			 /*! @brief Set if the collider is a trigger */
			// virtual void SetTrigger(bool isTrigger) = 0;

		};
	}
}