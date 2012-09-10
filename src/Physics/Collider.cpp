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
			center = NxVec3(NX_MAX_F32);
		}

		#pragma region ICollider Methods
		void Collider::SetMaterialIndex(int index)
		{
			materialIndex = index;
		}

		Vector3 Collider::GetCenterPos()
		{
			if (actor != 0)
				return actor->getGlobalPosition().get();
			else
				return center.get();
		}

		void Collider::SetCenterPos(const Vector3& center)
		{
			this->center = center.arr;
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
			/*if (actor != 0)
				return actor->getShapes()[0]->getFlag(NX_TRIGGER_ENABLE) != 0;
			else*/
			return isTrigger;
		}

		void Collider::SetTriggerFlag(bool triggerFlag)
		{
			this->isTrigger = triggerFlag;

			for (unsigned int i = 0; i < actor->getNbShapes(); i++)
				actor->getShapes()[i]->setFlag(NX_TRIGGER_ENABLE, isTrigger);
		}

		void Collider::SetCollisionGroup(UInt32 group)
		{
			if (actor == 0)
				return;

			for (unsigned int i = 0; i < actor->getNbShapes(); i++)
				actor->getShapes()[i]->setGroup(group);
		}
		#pragma endregion
	}
}