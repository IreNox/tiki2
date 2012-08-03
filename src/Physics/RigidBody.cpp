#include "Physics/RigidBody.h"

namespace TikiEngine 
{
	namespace Physics
	{
		RigidBody::RigidBody()
			: IRigidBody()
		{

			mass = 1;
			bodyDescription.mass = mass;

			velocity = Vector3::Zero;
			bodyDescription.linearVelocity = velocity.arr;

			angularVelocity = Vector3::Zero;
			bodyDescription.angularVelocity = angularVelocity.arr;
		}

		RigidBody::~RigidBody()
		{
			bodyDescription.setToDefault();
		}

		NxBodyDesc* RigidBody::GetDescription()
		{
			return &bodyDescription;
		}

		void RigidBody::SetActor(NxActor* setActor)
		{
			this->actor = setActor;
		}

		void RigidBody::SetMass(Single mass)
		{
			this->mass = mass;
			actor->setMass(mass);
		}

		Single RigidBody::GetMass()
		{
			return mass;
		}

		void RigidBody::SetVelocity(const Vector3& linearVelocity)
		{
			this->velocity = linearVelocity;
			actor->setLinearVelocity(linearVelocity.arr);

		}

		Vector3 RigidBody::GetVelocity()
		{
			return velocity;
		}

		void RigidBody::SetAngularVelocity(const Vector3& angularVelocity)
		{
			this->angularVelocity = angularVelocity;
			actor->setAngularVelocity(angularVelocity.arr);
		}
					
		Vector3 RigidBody:: GetAngularVelocity()
		{
			return angularVelocity;
		}



	}
}