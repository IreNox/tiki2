#pragma once

#include "Physics/Collider.h"
#include "Core/ICharacterController.h"
#include "PhysX/NxCharacter/NxCapsuleController.h"
#include "Physics/ControllerHitReport.h"

namespace TikiEngine 
{
	namespace Physics
	{
		class CharacterController : public ICharacterController, public Collider
		{

		public:
			CharacterController(Engine* engine, GameObject* gameObject);
			~CharacterController();

			// ICollider Methods
			IRigidBody* GetRigidBody();

			IPhysicsMaterial* GetMaterial() { return getInternMaterial(); }
			void SetMaterial(IPhysicsMaterial* mat) { }

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
			Single GetRealHeight() { return height + radius; }
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
            ControllerHitReport hitReport;
			Single radius;
			Single height;
			Single slopeLimit;
			Single stepOffset;

			UInt32 collisionFlags;
		};
	}
}