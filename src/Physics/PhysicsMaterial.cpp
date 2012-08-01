#include "Physics/PhysicsMaterial.h"

namespace TikiEngine
{
	namespace Components
	{
		PhysicsMaterial::PhysicsMaterial() : IPhysicsMaterial()
		{
			desc.setToDefault();
			material = PhysicsModule::GetScene()->createMaterial(desc);
			index = material->getMaterialIndex();
		}

		PhysicsMaterial::~PhysicsMaterial()
		{
			// TODO : call release here from object? 
			PhysicsModule::GetScene()->releaseMaterial(*material);
			material = NULL;
		}

		#pragma region IPhysicsMaterial Methods
		void PhysicsMaterial::SetDynamicFriction( Single dynFriction )
		{
			material->setDynamicFriction(dynFriction);
		}

		Single PhysicsMaterial::GetDynamicFriction()
		{
			return material->getDynamicFriction();
		}

		void PhysicsMaterial::SetStaticFriction( Single staFriction )
		{
			material->setStaticFriction(staFriction);
		}

		Single PhysicsMaterial::GetStaticFriction()
		{
			return material->getStaticFriction();
		}

		void PhysicsMaterial::SetRestitution( Single restitution )
		{
			material->setRestitution(restitution);
		}

		Single PhysicsMaterial::GetRestitution()
		{
			return material->getRestitution();
		}

		UInt16 PhysicsMaterial::GetIndex()
		{
			return index;
		}
		#pragma endregion

	}
}