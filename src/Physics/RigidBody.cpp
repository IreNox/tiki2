#include "Physics/RigidBody.h"

namespace TikiEngine 
{
	namespace Physics
	{
		RigidBody::RigidBody()
			: IRigidBody()
		{
			isKinematic = false;

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


		bool RigidBody::GetKinematic()
		{
			return isKinematic;
		}

		void RigidBody::SetKinematic(bool kinematicFlag)
		{
			this->isKinematic = kinematicFlag;

			if (isKinematic)
				actor->raiseBodyFlag(NX_BF_KINEMATIC);
			else
				actor->clearBodyFlag(NX_BF_KINEMATIC);

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


		void RigidBody::MovePosition(const Vector3& pos)
		{
			if (isKinematic)
			{
				// get world space position
				NxVec3 globalPos = actor->getGlobalPosition();
				globalPos += (NxVec3)pos.arr;
				actor->moveGlobalPosition(globalPos);
			}
		}

		void RigidBody::MoveRotation(const Quaternion& quat)
		{
			if (isKinematic)
			{
				NxQuat globalOrient = actor->getGlobalOrientationQuat();

				NxQuat q;
				q.setXYZW(quat.X, quat.Y, quat.Z, quat.W);
				actor->moveGlobalOrientationQuat(q * globalOrient);
				//actor->moveGlobalOrientationQuat(q3 * q2 * q1 * globalOrient); // Use global axes
				//actor->moveGlobalOrientationQuat(globalOrient * q1 * q2 * q3);   // Use local axes
			}
		}


	}
}