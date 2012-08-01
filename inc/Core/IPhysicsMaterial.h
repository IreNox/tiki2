#pragma once

#include "Core/Object.h"

namespace TikiEngine
{
	namespace Components
	{
		class IPhysicsMaterial : public Object
		{
		public:
			IPhysicsMaterial() : Object() {}
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