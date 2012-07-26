#pragma once

#include "Core/IModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		class IGraphics : public IModule
		{
		public:

			IGraphics(Engine* engine)
				: IModule(engine)
			{
			}
			virtual ~IGraphics() {}

			virtual void Draw() = 0;
		};
	}
}

