
#include "Core/TypeGlobals.h"
#include "Core/Engine.h"
#include "Core/LibraryManager.h"

#include "Resources/ContentManagerModule.h"
#include "Resources/FbxLoader.h"

#include <typeinfo.h>

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		ContentManagerModule::ContentManagerModule(Engine* engine)
			: IContentManager(engine) , fbxLoader(0)
		{
			wchar_t cd[MAX_PATH];
			_wgetcwd(cd, MAX_PATH);
			workingPath = cd;

			
		}

		ContentManagerModule::~ContentManagerModule()
		{
			//there is always this fucking dispose method u overlook
		}
		#pragma endregion

		#pragma region Member - Module
		bool ContentManagerModule::Initialize(EngineDescription& desc)
		{
			this->fbxLoader = new FbxLoader(engine);
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
			//delete fbxLoader;
			//fbxLoader = 0;
			SafeRelease(&this->fbxLoader);
		}
		#pragma endregion

		#pragma region Member - Load
		IResource* ContentManagerModule::Load(IntPtr hash, wstring name)
		{
			bool loadFile = true;
			IResource* value = 0;
			wstring fileName = this->GetRealFilePath(name);

			if (hash == typeid(ITexture).hash_code())
			{
				value = engine->librarys->CreateResource<ITexture>();
			}
			else if (hash == typeid(IShader).hash_code())
			{
				value = engine->librarys->CreateResource<IShader>();				
			}
			else if (hash == typeid(Mesh).hash_code())
			{
				value = fbxLoader->LoadMesh(fileName);
				loadFile = false;
			}

			if (loadFile && value != 0)
			{
				value->LoadFromFile(fileName.c_str());
			}

			return value;
		}
		#pragma endregion

		#pragma region Member - Load - Generic
		Mesh* ContentManagerModule::LoadMesh(const wstring& name)
		{
			return (Mesh*)this->Load(
				typeid(Mesh).hash_code(),
				name
			);
		}

		Mesh* ContentManagerModule::LoadFbxMesh(const wstring& name)
		{
			return this->fbxLoader->LoadMesh(name);
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
			Material* mat = new Material(engine);
			mat->SetShader(
				(IShader*)this->Load(
					typeid(IShader).hash_code(),
					name
				)
			);

			return mat;
		}
		#pragma endregion

		#pragma region Member - Path
		wstring ContentManagerModule::GetWorkingPath()
		{
			return workingPath;
		}

		wstring ContentManagerModule::GetRealFilePath(wstring fileName)
		{
			return workingPath + L"\\" + fileName;
		}
		#pragma endregion
	}
}