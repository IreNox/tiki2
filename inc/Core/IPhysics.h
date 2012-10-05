#pragma once

#include "Core/IModule.h"
#include "Core/Mesh.h"

#include "Core/PrimitiveTopologies.h"
#include "Core/Ray.h"

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

      virtual Boolean RayCast(Ray ray, RaycastHit* hitInfo, float distance = 1000.0f) = 0;

			void End() {}
			virtual void End(const UpdateArgs& args) = 0;

#if _DEBUG
			virtual void DrawDebug() = 0;
#endif

		};
	}
}