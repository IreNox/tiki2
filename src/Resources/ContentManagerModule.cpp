
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
			: IContentManager(engine) , fbxLoader(0), loadedResources()
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
			SafeRelease(&fbxLoader);
			
			//auto objects = loadedResources.GetValues();
		}
		#pragma endregion

		#pragma region Member - Load
		IResource* ContentManagerModule::Load(PInt hash, wstring name)
		{
			IResource* value = this->findLoadedResource(hash, name);

			if (value == 0)
			{
				bool loadFile = true;
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
					value = fbxLoader->LoadMesh(fileName); //fbxLoader->LoadSkeleton(fileName);
					loadFile = false;
				}
				else if (hash == typeid(IPhysicsMaterial).hash_code())
				{
					value = engine->librarys->CreateResource<IPhysicsMaterial>();
				}

				else if (hash == typeid(IBoundingBox).hash_code())
				{
					value = engine->librarys->CreateResource<IBoundingBox>();
				}

				if (value != 0)
				{
					loadedResources.Add(
						ResourceInfo(hash, name, value)
					);

					if (loadFile) value->LoadFromFile(fileName.c_str());
				}
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
		Mesh* ContentManagerModule::LoadFbxSkeletonMesh(const wstring& name)
		{
			return this->fbxLoader->LoadSkeleton(name);
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
			mat->GetShader()->Release();

			return mat;
		}

		IPhysicsMaterial* ContentManagerModule::LoadPhysicsMaterial(const wstring& name)
		{
			return (IPhysicsMaterial*)this->Load(
				typeid(IPhysicsMaterial).hash_code(), 
				name
			);
		}

		IBoundingBox* ContentManagerModule::LoadBoundingBox(const wstring& name)
		{
			return (IBoundingBox*)this->Load(
				typeid(IBoundingBox).hash_code(), 
				name
			);
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

		#pragma region Private Member
		IResource* ContentManagerModule::findLoadedResource(PInt hash, wstring name)
		{
			UInt32 i = 0;
			while (i < loadedResources.Count())
			{
				if (loadedResources[i].hash == hash && loadedResources[i].fileName == name)
				{
					return loadedResources[i].resource;
				}

				i++;
			}

			return 0;
		}
		#pragma endregion
	}
}
