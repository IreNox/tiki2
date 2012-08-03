#include "Physics/BoxCollider.h"
#include "Core/TypeGlobals.h"
#include "Physics/DllMain.h"

namespace TikiEngine 
{
	namespace Physics
	{
		BoxCollider::BoxCollider(Engine* engine, GameObject* gameObject)
				: IBoxCollider(engine, gameObject)
		{
			size = NxVec3(NX_MAX_F32);
			center = NxVec3(NX_MAX_F32);
		}

		BoxCollider::~BoxCollider()
		{
			//SafeRelease(&material);

			if (actor != 0)
				DllMain::Scene->releaseActor(*actor);
			actor = 0;
		}

		#pragma region IBoxCollider Methods
		Vector3 BoxCollider::GetCenter()
		{
			return center.get();
		}

		Vector3 BoxCollider::GetSize()
		{
			return size.get(); 
		}

		bool BoxCollider::GetDynamic()
		{
			return GetDynamicFlag();
		}

		void BoxCollider::SetSize(const Vector3& size)
		{
			this->size = size.arr;
			UpdateData();
		}

		void BoxCollider::SetCenter(const Vector3& center)
		{
			this->center = center.arr;
			UpdateData();
		}

		void BoxCollider::SetDynamic(bool dynamicFlag)
		{
			SetDynamicFlag(dynamicFlag);
			UpdateData();
		}

		bool BoxCollider::GetReady() 
		{
			return (size != NxVec3(NX_MAX_F32)) && 
				   (center != NxVec3(NX_MAX_F32)) && 
				   (state != CS_UNINITIALIZED);
		}

		#pragma endregion

		void BoxCollider::UpdateData()
		{
			if (!this->GetReady()) 
				return;

			if (actor != 0)
			{
				// reset the defaults for recreating from actorDesc.
				DllMain::Scene->releaseActor(*actor);
				actorDescription.setToDefault();
			}
			// Create Box shape description.
			NxBoxShapeDesc boxDesc;
			boxDesc.dimensions = size;
			boxDesc.localPose.t = NxVec3(0, size.y, 0);

			// Create material from index
			material.SetRestitution(1.0f);
			material.SetDynamicFriction(0.5f);
			material.SetStaticFriction(0.3f);
			boxDesc.materialIndex = material.GetIndex();

			// if we are dynamic, we have a Rigid Body attached
			if (state == CS_DYNAMIC)
			{
				NxBodyDesc bodyDesc;
				bodyDesc.mass = 1;
				actorDescription.body = &bodyDesc;
			}

			actorDescription.shapes.pushBack(&boxDesc);
			actorDescription.userData = (void*)this;	// associate with this object
			actorDescription.globalPose.t = center;

			// finally, create the actor from description
			actor = DllMain::Scene->createActor(actorDescription);
			rigidBody.SetActor(actor);

			// if this is or was a trigger or kinematic actor, raise the flags
			SetTriggerFlag(isTrigger);
			SetKinematicFlag(isKinematic);
		}
	}
}