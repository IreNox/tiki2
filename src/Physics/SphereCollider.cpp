#include "Physics/SphereCollider.h"
#include "Core/TypeGlobals.h"
#include "Physics/DllMain.h"

#include "Core/GameObject.h"

namespace TikiEngine 
{
	namespace Physics
	{
		SphereCollider::SphereCollider(Engine* engine, GameObject* gameObject)
				: ISphereCollider(engine, gameObject)
		{
			radius = NX_MAX_F32;
		}

		SphereCollider::~SphereCollider()
		{
			if (actor != 0)
				DllMain::Scene->releaseActor(*actor);
			actor = 0;
		}

		#pragma region ICollider Methods
		IRigidBody* SphereCollider::GetRigidBody()
		{
			return GetBody();
		}

		void SphereCollider::SetMaterial(int index)
		{
			SetMaterialIndex(index);
			UpdateData();
		}

		Vector3 SphereCollider::GetCenter()
		{
			return GetCenterPos();
		}

		void SphereCollider::SetCenter(const Vector3& center)
		{
			SetCenterPos(center);
			UpdateData();
		}

		bool SphereCollider::GetDynamic()
		{
			return GetDynamicFlag();
		}

		void SphereCollider::SetDynamic(bool dynamicFlag)
		{
			SetDynamicFlag(dynamicFlag);
			UpdateData();
		}

		bool SphereCollider::GetTrigger()
		{
			return GetTriggerFlag();
		}

		void SphereCollider::SetTrigger(bool triggerFlag)
		{
			SetTriggerFlag(triggerFlag);
		}

		void SphereCollider::SetGroup(CollisionGroups group)
		{
			SetCollisionGroup(group);
		}
		#pragma endregion

		#pragma region IBoxCollider Methods
		Single SphereCollider::GetRadius()
		{
			if (actor != 0)
				return actor->getShapes()[0]->isSphere()->getRadius();
			else 
				return radius; 
		}

		void SphereCollider::SetRadius(Single radius)
		{
			this->radius = radius;
			UpdateData();
		}

		bool SphereCollider::GetReady() 
		{
			return radius != NX_MAX_F32 && 
				   center != NxVec3(NX_MAX_F32) && 
				   state != CS_UNINITIALIZED &&
				   materialIndex != -1;
		}
		#pragma endregion

		void SphereCollider::UpdateData()
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
			NxSphereShapeDesc sphereDesc;
			sphereDesc.radius = radius;

			// Create material from index
			sphereDesc.materialIndex = materialIndex;

			// if we are dynamic, we have a Rigid Body attached
			if (state == CS_DYNAMIC)
				actorDescription.body = rigidBody.GetDescription();

			actorDescription.shapes.pushBack(&sphereDesc);
			actorDescription.userData = dynamic_cast<ICollider*>(this);	// associate the actor with this object
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

		void SphereCollider::Update(const UpdateArgs& args)
		{	
			gameObject->PRS.Position() = actor->getGlobalPosition().get();

			NxQuat rot = actor->getGlobalOrientationQuat();
			gameObject->PRS.Rotation() = Quaternion(rot.x, rot.y, rot.z, rot.w);
		}

	}
}
