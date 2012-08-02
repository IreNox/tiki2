#pragma once

#include "Core/ICollider.h"
#include "Physics/PhysicsMaterial.h"

namespace TikiEngine 
{
	namespace Physics
	{
		using namespace TikiEngine::Components;

		/*! @brief An abstract base class for all Physics colliders. */
		class Collider : public ICollider
		{

		public:
			 Collider(Engine* engine, GameObject* gameObject);
			 virtual ~Collider() {}


			 /*! @brief OnTriggerEnter is called when the Collider other enters the trigger. */
			 //virtual void OnTriggerEnter(Collider* other) = 0;

			 /*! @brief OnTriggerExit is called when the Collider other has stopped touching the trigger. */
			 //virtual void OnTriggerExit(Collider* other) = 0;

			 /*! @brief OnTriggerStay is called almost all the frames for every Collider other that is touching the trigger. */
			 //virtual void OnTriggerStay(Collider* other) = 0;


			 /*! @brief Is the collider a trigger? */
			// virtual bool IsTrigger() = 0;
			 
			 /*! @brief Sets whether the collider is a trigger or not */
			 //virtual void SetIsTrigger(bool setIsTrigger) = 0;


		 protected:
			 /*! @brief Enabled Colliders will collide with other colliders, disabled Colliders won't. */
			 bool enabled;
			 
			 /*! @brief The material used by the collider. */
			 PhysicsMaterial* material;
			 
			 /*! @brief Is the collider a trigger? */
			 bool isTrigger;
			 
			 /*! @brief This structure is used to save and load the state of NxActor objects. */
			 NxActorDesc actorDescription;
			 
			 /*! @brief the main simulation object in the physics SDK. An actor is owned by and contained in a NxScene */
			 NxActor* actor;

		};


	}
}