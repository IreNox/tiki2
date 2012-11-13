#include "Physics/TriggerReport.h"

#include "Core/ICollider.h"
#include "Core/ICharacterController.h"
#include "PhysX/Physics/NxActor.h"
#include "PhysX/Physics/NxShape.h"
namespace TikiEngine
{
	namespace Physics
	{
		using namespace TikiEngine::Components;

		void TriggerReport::onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status)
		{
			ICollider* triggerCollider = (ICollider*)triggerShape.getActor().userData;
			
			ICollider* otherCollider;
			if (otherShape.getActor().userData != 0)
				otherCollider = (ICollider*)otherShape.getActor().userData;
			else
				otherCollider = (ICollider*)otherShape.userData;
			


			if (status & NX_TRIGGER_ON_ENTER)
			{
				//OutputDebugString(L"Collider entered Trigger.\n");
			}

			if (status & NX_TRIGGER_ON_STAY)
			{
				//OutputDebugString(L"Collider stays in Trigger.\n");
			}

			if (status & NX_TRIGGER_ON_LEAVE)
			{
				//OutputDebugString(L"Collider leaved Trigger.\n");
			}

		}

	}
}