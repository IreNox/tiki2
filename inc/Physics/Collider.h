#pragma once

#include "Physics/PhysicsMaterial.h"


namespace TikiEngine 
{
	namespace Physics
	{
		class Collider
		{
		public: 
			Collider();
			virtual ~Collider() {}

			bool IsTrigger();
			//void SetTrigger(bool isTrigger);

		protected:
			bool isTrigger;
			NxActor* actor;
			NxActorDesc actorDescription;
			PhysicsMaterial material;
		};
	}
}