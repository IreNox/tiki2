#pragma once

#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Resources
	{
		class ContentManagerModule : public IContentManager
		{
		public:
			ContentManagerModule(Engine* engine);
			~ContentManagerModule(void);

			bool Initialize(EngineDescription& desc);

			void Begin();
			void End();

			void Dispose();

			void* Load(IntPtr hash, wstring name);

			Mesh* LoadMesh(wstring name);
			ITexture* LoadTexture(wstring name);
			Material* LoadMaterial(wstring name);
		};
	}
}

