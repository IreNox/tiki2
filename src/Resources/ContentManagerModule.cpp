
#include "Resources/ContentManagerModule.h"

#include "Core/Engine.h"
#include "Core/LibraryManager.h"
#include "Resources/FbxLoader.h"

#include <typeinfo.h>

namespace TikiEngine
{
	namespace Resources
	{
		ContentManagerModule::ContentManagerModule(Engine* engine)
			: IContentManager(engine)
		{
		}
		
		ContentManagerModule::~ContentManagerModule()
		{
		}

		bool ContentManagerModule::Initialize(EngineDescription& desc)
		{
			return true;
		}

		void ContentManagerModule::Begin()
		{
		}

		void ContentManagerModule::End()
		{
		}

		void ContentManagerModule::Dispose()
		{
		}

		void* ContentManagerModule::Load(IntPtr hash, wstring name)
		{
			if (hash == typeid(ITexture).hash_code())
			{
				ITexture* texture = engine->librarys->CreateResource<ITexture>();

				texture->LoadFromFile(name);
				return (void*) texture;
			}

			if (hash == typeid(Mesh).hash_code())
			{
				Mesh* iMesh = engine->librarys->CreateResource<Mesh>();

				return (void*)iMesh;
			}

			return 0;
		}

		Mesh* ContentManagerModule::LoadMesh(const wstring& name)
		{
			return (Mesh*)this->Load(
				typeid(Mesh).hash_code(),
				name
			);
		}
		Mesh* ContentManagerModule::LoadFbxMesh(const wstring& name)
		{
			return FbxLoader::LoadMesh(name);
		}

		ITexture* ContentManagerModule::LoadTexture(const wstring& name)
		{
			return (ITexture*)this->Load(
				typeid(ITexture).hash_code(),
				name
			);
		}

		Material* ContentManagerModule::LoadMaterial(const wstring& name)
		{
			return (Material*)this->Load(
				typeid(Material).hash_code(),
				name
			);
		}
	}
}