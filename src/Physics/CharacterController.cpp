#include "Physics/CharacterController.h"
#include "Physics/DllMain.h"

namespace TikiEngine 
{
	namespace Physics
	{
		CharacterController::CharacterController(Engine* engine, GameObject* gameObject)
				: ICharacterController(engine, gameObject)
		{
			controller = 0;
			
			center = NxVec3(NX_MAX_F32);
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

		bool CharacterController::GetDynamic()
		{
			// controllers are always dynamic!
			return true;
		}

		void CharacterController::SetDynamic(bool dynamicFlag)
		{
			//SetDynamicFlag(dynamicFlag);
			//UpdateData();
		}

		bool CharacterController::GetTrigger()
		{
			return GetTriggerFlag();
		}

		void CharacterController::SetTrigger(bool triggerFlag)
		{
			SetTriggerFlag(triggerFlag);
		}
		#pragma endregion

		#pragma region ICharacterController Methods
		Vector3 CharacterController::GetCenter()
		{
			return center.get();
		}

		void CharacterController::SetCenter(const Vector3& center)
		{
			this->center = center.arr;
			UpdateData();
		}

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
			desc.skinWidth	 = radius * 0.10f; //0.025;
			desc.stepOffset	 = stepOffset;
			desc.callback	 = 0; //TODO : &controllerHitReport;
			desc.userData	 = (void*)this;	
			controller = DllMain::ControllerManager->createController(DllMain::Scene, desc);

			// set the underlying kinematic actor from controller
			actor = controller->getActor();
			rigidBody.SetActor(actor);
		}

	}
}