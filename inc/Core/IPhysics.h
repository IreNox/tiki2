#pragma once

#include "Core/IModule.h"

namespace TikiEngine
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