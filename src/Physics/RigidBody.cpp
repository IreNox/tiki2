#include "Physics/RigidBody.h"

namespace TikiEngine 
{
	namespace Physics
	{
		RigidBody::RigidBody()
			: IRigidBody()
		{
			
		}

		RigidBody::~RigidBody()
		{

		}

		void RigidBody::SetActor(NxActor* setActor)
		{
			this->actor = setActor;
		}

		void RigidBody::SetMass(Single mass)
		{
			actor->setMass(mass);
		}

		Single RigidBody::GetMass()
		{
			return actor->getMass();
		}

	}
}