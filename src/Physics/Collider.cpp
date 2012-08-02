#include "Physics/Collider.h"

namespace TikiEngine 
{
	namespace Physics
	{
		Collider::Collider()
		{
			isDynamic = true;
			isTrigger = false;
			isKinematic = false;
		}

		bool Collider::GetTriggerFlag()
		{
			return isTrigger;
		}

		void Collider::SetTriggerFlag(bool triggerFlag)
		{
			this->isTrigger = triggerFlag;

			for (unsigned int i = 0; i < actor->getNbShapes(); i++)
			{
				actor->getShapes()[i]->setFlag(NX_TRIGGER_ENABLE, isTrigger);

			}
		}

		bool Collider::GetKinematicFlag()
		{
			return isKinematic;
		}

		void Collider::SetKinematicFlag(bool kinematicFlag)
		{
			this->isKinematic = kinematicFlag;

			if (isKinematic)
				actor->raiseBodyFlag(NX_BF_KINEMATIC);
			else
				actor->clearBodyFlag(NX_BF_KINEMATIC);

		}

	}
}