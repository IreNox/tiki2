#pragma once

#include "Core/Component.h"
#include "Core/IRigidBody.h"
#include "Core/EventTriggers.h"

namespace TikiEngine
{
	namespace Components
	{
		//using namespace TikiEngine;

		enum CollisionGroups
		{
			CG_Non_Collidable,
			CG_Collidable_Non_Pushable,
			CG_Collidable_Pushable
		};

		/*! @brief An Interface of all colliders. */
		class ICollider : public Component
		{
		public:

			/*! @brief Create Collider Component */
			ICollider(Engine* engine, GameObject* gameObject)
				: Component(engine, gameObject)
			{
			}
			virtual ~ICollider() {}


			virtual void SetMaterial(int index) = 0;

			/* !@brief This will offset the Capsule Collider in world space. */
			virtual Vector3 GetCenter() = 0;
			virtual void SetCenter(const Vector3& center) = 0;
			
			/* !@brief True if this Collider is dynamic, false otherwise */
			virtual bool GetDynamic() = 0;
			/* !@brief Set if the Collider should be dynamicor static */
			virtual void SetDynamic(bool dynamicFlag) = 0;

			 /*! @brief Is this collider a trigger? */
			virtual bool GetTrigger() = 0;
			/*! @brief Set if the collider is a trigger or not */
			virtual void SetTrigger(bool triggerFlag) = 0;

			/* !@brief gets the underlying Rigid Body if this is a dynamic actor! So ensure that this collider is set to Dynamic before! */
			virtual IRigidBody* GetRigidBody() = 0;

			/* !@brief Sets the collision group */
			virtual void SetGroup(CollisionGroups group) = 0;



			 /* !@brief OnTriggerEnter is called when the Collider other enters the trigger. */
			 //virtual void OnTriggerEnter(ICollider* other) = 0;
			TriggerEnterEvent TriggerEnter;

			/* !@brief OnTriggerStay is called almost all the frames for every Collider other that is touching the trigger. */
			//virtual void OnTriggerStay(ICollider* other) = 0;
			TriggerStayEvent TriggerStay;

			 /* !@brief OnTriggerExit is called when the Collider other has stopped touching the trigger. */
			 //virtual void OnTriggerExit(ICollider* other) = 0;
			TriggerExitEvent TriggerExit;
		};
	}
}