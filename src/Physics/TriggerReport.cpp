#include "Physics/TriggerReport.h"

#include "Core/ICollider.h"
//#include "Core/EventTriggers.h"

#include "PhysX/Physics/NxActor.h"


namespace TikiEngine
{
	namespace Physics
	{
		using namespace TikiEngine::Components;

		void TriggerReport::onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status)
		{
			ICollider* triggerCollider = 0;
			triggerCollider = static_cast<ICollider*>(triggerShape.getActor().userData);
			ICollider* otherCollider = 0;
			otherCollider = static_cast<ICollider*>(otherShape.getActor().userData);

			if (triggerCollider != 0 && otherCollider != 0)
			{
				if (!otherCollider->GetTrigger())
				{
					if (status & NX_TRIGGER_ON_ENTER)
					{
						TriggerEnterArgs args = TriggerEnterArgs(triggerCollider, otherCollider);
						triggerCollider->TriggerEnter.RaiseEvent(triggerCollider, args);
					}
					if (status & NX_TRIGGER_ON_STAY)
					{
						TriggerStayArgs args = TriggerStayArgs(triggerCollider, otherCollider);
						triggerCollider->TriggerStay.RaiseEvent(triggerCollider, args);
					}
					if (status & NX_TRIGGER_ON_LEAVE)
					{
						TriggerExitArgs args = TriggerExitArgs(triggerCollider, otherCollider);
						triggerCollider->TriggerExit.RaiseEvent(triggerCollider, args);
					}
				} // if (!Trigger)
			}


		}

	}
}