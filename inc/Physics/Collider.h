#pragma once

#include "Core/ICollider.h"

namespace TikiEngine 
{
	namespace Components
	{


		class Collider : public ICollider
		{

		public:
			 Collider(Engine* engine, GameObject* gameObject) 
				: ICollider(engine, gameObject) { }

			/*! @brief OnTriggerEnter is called when the Collider other enters the trigger. */
			virtual void OnTriggerEnter(Collider* other) = 0;

			/*! @brief OnTriggerExit is called when the Collider other has stopped touching the trigger. */
			virtual void OnTriggerExit(Collider* other) = 0;

			/*! @brief OnTriggerStay is called almost all the frames for every Collider other that is touching the trigger. */
			virtual void OnTriggerStay(Collider* other) = 0;

			/*! @brief Is the collider a trigger? */
			virtual bool IsTrigger() = 0;


		protected:
			/*! @brief Enabled Colliders will collide with other colliders, disabled Colliders won't. */
			bool enabled;

			/*! @brief The material used by the collider. */
			//PhysicsMaterial material;

			/*! @brief Is the collider a trigger? */
			bool isTrigger;
		};


	}
}