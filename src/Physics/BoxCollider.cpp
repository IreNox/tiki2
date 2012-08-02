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

		bool BoxCollider::GetReady() 
		{
			return (size != NxVec3(NX_MAX_F32)) && (center != NxVec3(NX_MAX_F32));
		}
		#pragma endregion

		void BoxCollider::UpdateData()
		{
			if (!this->GetReady()) 
				return;

			if (actor != 0)
				DllMain::Scene->releaseActor(*actor);

			// Create Box shape description.
			NxBoxShapeDesc boxDesc;
			boxDesc.dimensions = size;
			boxDesc.localPose.t = NxVec3(0, size.y, 0);

			// Create material from index
			material.SetRestitution(1.0f);
			material.SetDynamicFriction(0.5f);
			material.SetStaticFriction(0.3f);
			boxDesc.materialIndex = material.GetIndex();

			// if we have a trigger shape, events are sent to the user
			if (isTrigger)
				boxDesc.shapeFlags |= NX_TRIGGER_ENABLE;
			else
			{
				// Triggers have no body description
				//  TODO init RigidBody class here :)
				NxBodyDesc bodyDesc;
				bodyDesc.mass = 10;
				actorDescription.body = &bodyDesc;
			}

			actorDescription.shapes.pushBack(&boxDesc);
			actorDescription.userData = (void*)this;	// associate with this object
			actorDescription.globalPose.t = center;

			// finally, create the actor from description
			actor = DllMain::Scene->createActor(actorDescription);

			// rest the defaults for recreation, else more and more shapes are added
			actorDescription.setToDefault();
		}
	}
}