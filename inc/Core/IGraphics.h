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

			void Begin() {}
			virtual void Begin(const DrawArgs& args) = 0;
						
			virtual void* GetDevice() = 0;
			virtual void* GetDeviceContext() = 0;
		};
	}
}

