#pragma once

#include "Core/IModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		class IPhysics : public IModule
		{
		public:

			IPhysics(Engine* engine)
				: IModule(engine)
			{
			}
			virtual ~IPhysics() {}

			virtual void DoWhatIWant() = 0;
		};
	}
}