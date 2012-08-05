#include "Physics/Collider.h"

namespace TikiEngine 
{
	namespace Physics
	{
		Collider::Collider()
		{
			materialIndex = -1;
			actor = 0;
			state = CS_UNINITIALIZED;
			isTrigger = false;
			//isKinematic = false;
		}

		#pragma region ICollider Methods

		void Collider::SetMaterialIndex(int index)
		{
			materialIndex = index;
		}

		bool Collider::GetDynamicFlag()
		{
			if (state == CS_DYNAMIC)
				return true;
			else
				return false;
		}

		
		void Collider::SetDynamicFlag(bool dynamicFlag)
		{
			if (dynamicFlag)
				state = CS_DYNAMIC;
			else
				state = CS_STATIC;
		}


		bool Collider::GetTriggerFlag()
		{
			return isTrigger;
			//actor->getShapes()[0]->getFlag(NX_TRIGGER_ENABLE);
		}

		void Collider::SetTriggerFlag(bool triggerFlag)
		{
			this->isTrigger = triggerFlag;

			for (unsigned int i = 0; i < actor->getNbShapes(); i++)
			{
				actor->getShapes()[i]->setFlag(NX_TRIGGER_ENABLE, isTrigger);
			}
		}
		#pragma endregion

	}
}