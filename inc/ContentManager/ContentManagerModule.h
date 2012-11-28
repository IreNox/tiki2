#pragma once

#include "Core/IContentManager.h"

#include "ContentManager/ResourceInfo.h"

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

			IResource* Load(PInt hash, wstring name);

			Mesh* LoadMesh(const wstring& name);
			IModel* LoadModel(const wstring& name);

			ITexture* LoadTexture(const wstring& name);

			IShader* LoadShader(const wstring& name);
			Material* LoadMaterial(const wstring& name);

			IPhysicsMaterial* LoadPhysicsMaterial(const wstring& name);
			IBoundingBox* LoadBoundingBox(const wstring& name);

			void ReleaseResource(IResource* res);

		private:
			
			bool disposing;
			List<ResourceInfo> loadedResources;

			#if _DEBUG
			DWORD threadId;
			HANDLE threadHandle;
			CRITICAL_SECTION threadCriticle;

			wstring filePath;
			List<wstring> changedFiles;

			static void initThread();
			void threadDynamicReload();
			#endif

			IResource* findLoadedResource(PInt hash, wstring name);

		};
	}
}

