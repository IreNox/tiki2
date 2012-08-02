#include "Physics/Collider.h"

namespace TikiEngine 
{
	namespace Physics
	{
		Collider::Collider()
		{
			isTrigger = false;
		}

		bool Collider::IsTrigger()
		{
			return isTrigger;
		}

		//void Collider::SetTrigger(bool isTrigger)
		//{
		//	this->isTrigger = isTrigger;

		//	// TODO ^^
		//	//actor->getShapes()[0]->setFlag(NX_TRIGGER_ENABLE, true);
		//}

	}
}