#pragma once

#include "PhysX/Physics/NxUserContactReport.h"

namespace TikiEngine
{
	namespace Physics
	{
		class TriggerReport : public NxUserTriggerReport
		{
		public:
			virtual void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);
		};

	}
}