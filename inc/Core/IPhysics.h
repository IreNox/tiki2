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

#if _DEBUG
			virtual void FillDebugMesh(Dictionary<PrimitiveTopologies, Mesh*>* list) = 0;
#endif

		};
	}
}