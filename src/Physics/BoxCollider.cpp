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

		#pragma region ICollider Methods
		IRigidBody* BoxCollider::GetRigidBody()
		{
			return GetBody();
		}

		void BoxCollider::SetMaterial(int index)
		{
			SetMaterialIndex(index);
			UpdateData();
		}

		bool BoxCollider::GetDynamic()
		{
			return GetDynamicFlag();
		}

		void BoxCollider::SetDynamic(bool dynamicFlag)
		{
			SetDynamicFlag(dynamicFlag);
			UpdateData();
		}

		bool BoxCollider::GetTrigger()
		{
			return GetTriggerFlag();
		}

		// don't update here, just raise the flag after recreation
		void BoxCollider::SetTrigger(bool triggerFlag)
		{
			SetTriggerFlag(triggerFlag);
		}
		#pragma endregion

		#pragma region IBoxCollider Methods
		Vector3 BoxCollider::GetSize()
		{
			return size.get(); 
		}

		void BoxCollider::SetSize(const Vector3& size)
		{
			this->size = size.arr;
			UpdateData();
		}

		Vector3 BoxCollider::GetCenter()
		{
			return center.get();
		}

		void BoxCollider::SetCenter(const Vector3& center)
		{
			this->center = center.arr;
			UpdateData();
		}

		bool BoxCollider::GetReady() 
		{
			return (size != NxVec3(NX_MAX_F32)) && 
				   (center != NxVec3(NX_MAX_F32)) && 
				   (state != CS_UNINITIALIZED) &&
				   (materialIndex != -1);
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
			boxDesc.materialIndex = materialIndex;

			// if we are dynamic, we have a Rigid Body attached
			if (state == CS_DYNAMIC)
				actorDescription.body = rigidBody.GetDescription();

			actorDescription.shapes.pushBack(&boxDesc);
			actorDescription.userData = (void*)this;	// associate the actor with this object
			actorDescription.globalPose.t = center;

			// finally, create the actor from description
			actor = DllMain::Scene->createActor(actorDescription);

			// (re) set the actor object the rigidBody belongs to if this is a dynamic actor.
			if (state == CS_DYNAMIC)
				rigidBody.SetActor(actor);

			// if this is or was a trigger or kinematic actor, raise the flags
			SetTriggerFlag(isTrigger);
			//SetKinematicFlag(rigidBody.GetKinematic());
		}
	}
}