#pragma once

#include "Core/Engine.h"
#include "Core/EngineObject.h"

//#include "Core/EngineDescription.h"

namespace TikiEngine
{
	namespace Modules
	{
		using TikiEngine::Description::EngineDescription;

		class IModule : public EngineObject
		{
		public:

			IModule(Engine* engine)
				: EngineObject(engine)
			{
			}

			virtual ~IModule()
			{
			}

			virtual bool Initialize(EngineDescription& desc) = 0;

			virtual void Begin() = 0;
			virtual void End() = 0;

			virtual void Dispose() = 0;
		};

	}
}
