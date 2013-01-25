
#include "Physics/Collider.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine 
{
	namespace Physics
	{
		Collider::Collider()
		{
			material = 0;
			actor = 0;
			state = CS_UNINITIALIZED;
			isTrigger = false;
			center = NxVec3(NX_MAX_F32);
			rigidBody = TIKI_NEW RigidBody();
		}

		Collider::~Collider()
		{
			SafeRelease(&material);
			SafeRelease(&rigidBody);
		}

		#pragma region ICollider Methods
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

			if (actor)
			{
				actor->setGlobalPosition(this->center);
			}
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

		void Collider::SetCollisionGroup(unsigned short group)
		{
			this->group = group;

			if (actor == 0)
				return;

			for (unsigned int i = 0; i < actor->getNbShapes(); i++)
				actor->getShapes()[i]->setGroup(group);
		}
		#pragma endregion

		bool Collider::GetReady()
		{
			return  (center != NxVec3(NX_MAX_F32)) && 
					(state != CS_UNINITIALIZED);
		}
	}
}