#pragma once

#include "Core/IModule.h"
#include "Core/InputState.h"

namespace TikiEngine
{
	namespace Modules
	{
		class IInput : public IModule
		{
		public:

			IInput(Engine* engine)
				: IModule(engine)
			{
			}
			virtual ~IInput() {}

			virtual void FillInputState(InputState* state) = 0;
		};
	}
}

