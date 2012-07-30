#pragma once

#include "Core/IModule.h"

#include "Core/Mesh.h"
#include "Core/ITexture.h"
#include "Core/Material.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Graphics;

		class IContentManager : public IModule
		{
		public:

			IContentManager(Engine* engine)
				: IModule(engine)
			{
			}
			virtual ~IContentManager() {}

			virtual void* Load(IntPtr hash, wstring name) = 0;

			virtual Mesh* LoadMesh(wstring name) = 0;
			virtual ITexture* LoadTexture(wstring name) = 0;
			virtual Material* LoadMaterial(wstring name) = 0;

		};
	}
}