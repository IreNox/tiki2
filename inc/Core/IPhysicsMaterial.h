#pragma once

#include "Core/IResource.h"

namespace TikiEngine
{
	namespace Resources
	{
		class IPhysicsMaterial : public IResource
		{
		public:
			IPhysicsMaterial(Engine* engine) 
				: IResource(engine) {}

			virtual ~IPhysicsMaterial() {}

			virtual void SetDynamicFriction(Single dynFriction) = 0;
			virtual Single GetDynamicFriction() = 0;

			virtual void SetStaticFriction(Single staFriction) = 0;
			virtual Single GetStaticFriction() = 0;

			virtual void SetRestitution(Single restitution) = 0;
			virtual Single GetRestitution() = 0;

			virtual UInt16 GetIndex() = 0;
		};
	}
}