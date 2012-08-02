#include "Physics/BoxCollider.h"
#include "Core/TypeGlobals.h"
#include "Physics/DllMain.h"

namespace TikiEngine 
{
	namespace Physics
	{

		BoxCollider::BoxCollider(Engine* engine, GameObject* gameObject, 
                             NxVec3 setCenter, NxVec3 setSize, bool setIsTrigger)
				: Collider(engine, gameObject)
		{
			center = setCenter;
			size = setSize;
			isTrigger = setIsTrigger;
		}

		BoxCollider::~BoxCollider()
		{
      SafeRelease(&material);

			if (actor != NULL)
				DllMain::Scene->releaseActor(*actor);
			actor = NULL;
		}

		bool BoxCollider::GetReady() 
			{
				// Create Box shape description.
				NxBoxShapeDesc boxDesc;
				boxDesc.dimensions = size;
				boxDesc.localPose.t = NxVec3(0, size.y, 0);

				// Create material from index
				material = new PhysicsMaterial();
				material->SetRestitution(1.0f);
				material->SetRestitution(0.5f);
				material->SetRestitution(0.3f);
				boxDesc.materialIndex = material->GetIndex();

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

				if (actor == NULL)
					return false;

				return true;
			}

	}
}