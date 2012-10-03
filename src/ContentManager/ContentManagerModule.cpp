
#include "Core/TypeGlobals.h"
#include "Core/Engine.h"
#include "Core/LibraryManager.h"

#include "ContentManager/ContentManagerModule.h"

#include "Core/MeshIndexed.h"
#include "Core/DefaultVertex.h"

#include <typeinfo.h>

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		ContentManagerModule::ContentManagerModule(Engine* engine)
			: IContentManager(engine) , loadedResources()
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
			//UInt32 i = 0;
			//while (i < loadedResources.Count())
			//{
			//	while (loadedResources[i].resource->Release()) { }
			//	i++;
			//}
			//loadedResources.Clear();
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
					MeshIndexed* mesh = new MeshIndexed(engine);
					loadFile = false;

					IModel* model = this->LoadModel(name);

					UInt32* indices = 0;
					void* vertices = 0;

					UInt32 indicesCount = 0;
					UInt32 verticesCount = 0;

					model->GetIndexData(&indices, &indicesCount);
					model->GetVertexData(&vertices, &verticesCount);

					mesh->SetIndexData(indices, indicesCount);
					mesh->SetVertexData(vertices, verticesCount);

					mesh->SetVertexDeclaration(TikiEngine::Vertices::DefaultVertex::Declaration, TikiEngine::Vertices::DefaultVertex::DeclarationCount);

					SafeRelease(&model);

					value = mesh;
				}
				else if (hash == typeid(IModel).hash_code())
				{
					value = engine->librarys->CreateResource<IModel>();
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
					value->AddRef();

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

		IModel* ContentManagerModule::LoadModel(const wstring& name)
		{
			return (IModel*)this->Load(
				typeid(IModel).hash_code(),
				name
			);
		}

		ITexture* ContentManagerModule::LoadTexture(const wstring& name)
		{
			return (ITexture*)this->Load(
				typeid(ITexture).hash_code(),
				name
			);
		}

		IShader* ContentManagerModule::LoadShader(const wstring& name)
		{
			return (IShader*)this->Load(
				typeid(IShader).hash_code(),
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
					loadedResources[i].resource->AddRef();
					return loadedResources[i].resource;
				}

				i++;
			}

			return 0;
		}
		#pragma endregion
	}
}
