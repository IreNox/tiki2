#pragma once

#include "Core/IModule.h"
#include "Core/Mesh.h"

#include "Core/PrimitiveTopologies.h"

namespace TikiEngine
{
	namespace Modules
	{
		using TikiEngine::Resources::Mesh;

		class IPhysics : public IModule
		{
		public:

			IPhysics(Engine* engine)
				: IModule(engine)
			{
			}
			virtual ~IPhysics() {}

			void End() {}
			virtual void End(const UpdateArgs& args) = 0;

#if _DEBUG
			virtual void DrawDebug() = 0;
#endif

		};
	}
}