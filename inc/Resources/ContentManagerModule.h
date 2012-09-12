#pragma once

#include "Core/IContentManager.h"
#include "Resources/FbxLoader.h"

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

			IResource* Load(IntPtr hash, wstring name);

			Mesh* LoadMesh(const wstring& name);
			Mesh* LoadFbxMesh(const wstring& name);
			Mesh* LoadFbxSkeletonMesh(const wstring& name);
			ITexture* LoadTexture(const wstring& name);
			Material* LoadMaterial(const wstring& name);
			IPhysicsMaterial* LoadPhysicsMaterial(const wstring& name);

			wstring GetWorkingPath();
			wstring GetRealFilePath(wstring fileName);

		private:

			wstring workingPath;

			FbxLoader *fbxLoader;

			//Dictionary<UInt32, Object*> loadedResources;

		};
	}
}

