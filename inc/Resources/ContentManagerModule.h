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

			Mesh* LoadMesh(const wstring& name);
			Mesh* LoadFbxMesh(const wstring& name);
			ITexture* LoadTexture(const wstring& name);
			Material* LoadMaterial(const wstring& name);
		};
	}
}

