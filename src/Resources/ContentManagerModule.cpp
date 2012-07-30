
#include "Resources/ContentManagerModule.h"

#include "Core/Engine.h"
#include "Core/LibraryManager.h"

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
			}

			return 0;
		}

		Mesh* ContentManagerModule::LoadMesh(wstring name)
		{
			return (Mesh*)this->Load(
				typeid(Mesh).hash_code(),
				name
			);
		}

		ITexture* ContentManagerModule::LoadTexture(wstring name)
		{
			return (ITexture*)this->Load(
				typeid(ITexture).hash_code(),
				name
			);
		}

		Material* ContentManagerModule::LoadMaterial(wstring name)
		{
			return (Material*)this->Load(
				typeid(Material).hash_code(),
				name
			);
		}
	}
}