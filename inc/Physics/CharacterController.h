#pragma once

#include "Physics/Collider.h"
#include "Core/ICharacterController.h"
#include "PhysX/NxCharacter/NxCapsuleController.h"

namespace TikiEngine 
{
	namespace Physics
	{
		class CharacterController : public Collider, public ICharacterController
		{

		public:
			CharacterController(Engine* engine, GameObject* gameObject);
			~CharacterController();

			// ICollider Methods
			IRigidBody* GetRigidBody();
			void SetMaterial(int index);

			Vector3 GetCenter();
			void SetCenter(const Vector3& center);

			bool GetDynamic();
			void SetDynamic(bool dynamicFlag);

			bool GetTrigger();
			void SetTrigger(bool triggerFlag);

			void SetGroup(CollisionGroups group);

			// ICharacterController Methods


			Single GetRadius();
			void SetRadius(Single radius); 

			Single GetHeight();
			void SetHeight(Single height); 

			Single GetSlopeLimit();
			void SetSlopeLimit(Single slopeLimit);

			Single GetStepOffset();
			void SetStepOffset(Single stepOffset);

			CollisionFlags Move(const Vector3& displacement);

			// Component Methods
			bool GetReady();

			void Update(const UpdateArgs& args);
			void Draw(const DrawArgs& args) {}

		private:
			/*! @brief (re)Initialize BoxCollider */
			void UpdateData();

		private:
			NxCapsuleControllerDesc desc;
			NxController* controller;
			Single radius;
			Single height;
			Single slopeLimit;
			Single stepOffset;

			UInt32 collisionFlags;
		};
	}
}