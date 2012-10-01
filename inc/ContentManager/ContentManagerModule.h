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

			IResource* Load(PInt hash, wstring name);

			Mesh* LoadMesh(const wstring& name);
			IModel* LoadModel(const wstring& name);
			ITexture* LoadTexture(const wstring& name);
			Material* LoadMaterial(const wstring& name);
			IPhysicsMaterial* LoadPhysicsMaterial(const wstring& name);
			IBoundingBox* LoadBoundingBox(const wstring& name);

			wstring GetWorkingPath();
			wstring GetRealFilePath(wstring fileName);

		private:

			struct ResourceInfo
			{
				ResourceInfo() : hash(0), fileName(), resource(0) {}
				ResourceInfo(PInt hash, wstring name, IResource* res) : hash(hash), fileName(name), resource(res) {}

				~ResourceInfo() { fileName.erase(); }

				PInt hash;
				wstring fileName;
				IResource* resource;
			};

			IResource* findLoadedResource(PInt hash, wstring name);

			wstring workingPath;

			List<ResourceInfo> loadedResources;

		};
	}
}

