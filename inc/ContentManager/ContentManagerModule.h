#pragma once

#include "Core/IContentManager.h"

#include "ContentManager/ResourceInfo.h"
#include "ContentManager/ResourceBinaryData.h"

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

			Stream* LoadData(wstring name);
			IResource* Load(PInt hash, wstring name);

			Mesh* LoadMesh(const wstring& name);
			IModel* LoadModel(const wstring& name);

			ISound* LoadSound(const wstring& name);
			ISound3D* LoadSound3D(const wstring& name);

			ITexture* LoadTexture(const wstring& name);

			IShader* LoadShader(const wstring& name);
			Material* LoadMaterial(const wstring& name);

			IPhysicsMaterial* LoadPhysicsMaterial(const wstring& name);
			IBoundingBox* LoadBoundingBox(const wstring& name);

			void ReleaseResource(IResource* res);

		private:
			
			bool disposing;
			List<ResourceInfo> loadedResources;

			ResIOContext* resourceContext;
			Dictionary<wstring, UInt32> resourcePackage;

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

