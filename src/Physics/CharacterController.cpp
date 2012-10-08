#include "Physics/CharacterController.h"
#include "Physics/DllMain.h"

#include "Core/GameObject.h"

namespace TikiEngine 
{
	namespace Physics
	{
		CharacterController::CharacterController(Engine* engine, GameObject* gameObject)
				: ICharacterController(engine, gameObject)
		{
			controller = 0;
			
			radius = FLT_MAX;
			height = FLT_MAX;
			slopeLimit = FLT_MAX;
			stepOffset = FLT_MAX;

			state = CS_DYNAMIC;
		}

		CharacterController::~CharacterController()
		{
			if (controller != 0)
				DllMain::ControllerManager->releaseController(*controller);
			controller = 0;
		}

		#pragma region ICollider Methods
		IRigidBody* CharacterController::GetRigidBody()
		{
			return GetBody();
		}

		void CharacterController::SetMaterial(int index)
		{
			// not supported
			//SetMaterialIndex(index);
			//UpdateData();
		}

		Vector3 CharacterController::GetCenter()
		{
			return GetCenterPos();
		}

		void CharacterController::SetCenter(const Vector3& center)
		{
			SetCenterPos(center);
			UpdateData();
		}

		bool CharacterController::GetDynamic()
		{
			// controllers are always dynamic kinematic actors!
			return true;
		}

		void CharacterController::SetDynamic(bool dynamicFlag)
		{
			//SetDynamicFlag(dynamicFlag);
			//UpdateData();
		}

		bool CharacterController::GetTrigger()
		{
			return false;
			//return GetTriggerFlag();
		}

		void CharacterController::SetTrigger(bool triggerFlag)
		{
			// not supported by physX?
			//SetTriggerFlag(triggerFlag);
		}

		void CharacterController::SetGroup(CollisionGroups group)
		{
			SetCollisionGroup(group);
		}

		#pragma endregion

		#pragma region ICharacterController Methods
		Single CharacterController::GetRadius()
		{
			return radius;
		}

		void CharacterController::SetRadius(Single radius)
		{
			this->radius = radius;
			UpdateData();
		}

		Single CharacterController::GetHeight()
		{
			return height;
		}

		void CharacterController::SetHeight(Single height)
		{
			this->height = height;
			UpdateData();
		}

		Single CharacterController::GetSlopeLimit()
		{
			return slopeLimit;
		}

		void CharacterController::SetSlopeLimit(Single slopeLimit)
		{
			this->slopeLimit = slopeLimit;
			UpdateData();
		}

		Single CharacterController::GetStepOffset()
		{
			return stepOffset;
		}

		void CharacterController::SetStepOffset(Single stepOffset)
		{
			this->stepOffset = stepOffset;
			UpdateData();
		}


		CollisionFlags CharacterController::Move(const Vector3& displacement)
		{
			NxU32 activeGroups = (1<<CG_Collidable_Non_Pushable) | 
								 (1<<CG_Collidable_Pushable);

			NxF32 minDist = 0.000001f;
			controller->move(displacement.arr, activeGroups, 
							 minDist, collisionFlags);

			return (CollisionFlags)collisionFlags;

		}

		#pragma endregion

		bool CharacterController::GetReady() 
		{
			return center != NxVec3(NX_MAX_F32) &&
				   radius != FLT_MAX &&
				   height != FLT_MAX &&
				   slopeLimit != FLT_MAX &&
				   stepOffset != FLT_MAX;
		}

		void CharacterController::UpdateData()
		{
			if (!this->GetReady()) 
				return;

			if (controller != 0)
			{
				// reset the defaults for recreating from actorDesc.
				DllMain::ControllerManager->releaseController(*controller);
				desc.setToDefault();
			}

			desc.position	 = NxExtendedVec3(center.x, center.y, center.z);
			desc.radius		 = radius;
			desc.height		 = height;
			desc.upDirection = NX_Y;
			desc.slopeLimit	 = cosf(NxMath::degToRad(slopeLimit));
			desc.skinWidth	 = radius * 0.10f; // make it 10% of radius, gives best results (unity doc)
			desc.stepOffset	 = stepOffset;
			desc.callback	 = 0; //TODO : &controllerHitReport;
			desc.userData	 = dynamic_cast<ICollider*>(this);	
			controller = DllMain::ControllerManager->createController(DllMain::Scene, desc);

			// set the underlying kinematic actor from controller
			actor = controller->getActor();
			rigidBody.SetActor(actor);
		}

		void CharacterController::Update(const UpdateArgs& args)
		{
			gameObject->PRS.SetPosition(actor->getGlobalPosition().get());

			// controllers have no rotation!
		}

	}
}
