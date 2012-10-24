
#include "Core/TypeGlobals.h"
#include "Core/HelperLog.h"
#include "Core/HelperPath.h"

#include "Core/Engine.h"
#include "Core/LibraryManager.h"

#include "ContentManager/ContentManagerModule.h"
#include "ContentManager/DllMain.h"

#include <typeinfo.h>

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		ContentManagerModule::ContentManagerModule(Engine* engine)
			: IContentManager(engine) , loadedResources()
		{
		}

		ContentManagerModule::~ContentManagerModule()
		{
			//there is always this fucking dispose method u overlook
		}
		#pragma endregion

		#pragma region Member - Module
		bool ContentManagerModule::Initialize(EngineDescription& desc)
		{
			#if _DEBUG
			InitializeCriticalSection(&threadCriticle);

			threadHandle = CreateThread(
				0,
				2000,
				(LPTHREAD_START_ROUTINE)initThread,
				0,
				THREAD_TERMINATE,
				&threadId
			);
			#endif

			return true;
		}

		void ContentManagerModule::Begin()
		{
			#if _DEBUG
			EnterCriticalSection(&threadCriticle);

			UInt32 i = 0;
			while (i < changedFiles.Count())
			{
				UInt32 a = 0;
				while (a < loadedResources.Count())
				{
					if (loadedResources[a].fileName == changedFiles[i])
					{
						try
						{
							loadedResources[a].resource->LoadFromFile(
								changedFiles[i].c_str()
							);
						}
						catch (const char*)
						{
							HelperLog::Write("Can't reload Resource");
						}
						catch (const wchar_t*)
						{
							HelperLog::Write("Can't reload Resource");
						}
						catch (wstring)
						{
							HelperLog::Write("Can't reload Resource");
						}
						catch (string)
						{
							HelperLog::Write("Can't reload Resource");
						}
					}

					a++;
				}

				i++;
			}
			changedFiles.Clear();

			LeaveCriticalSection(&threadCriticle);
			#endif
		}

		void ContentManagerModule::End()
		{
			
		}

		void ContentManagerModule::Dispose()
		{
			#if _DEBUG
			TerminateThread(threadHandle, 0);
			#endif

			UInt32 i = 0;
			while (i < loadedResources.Count())
			{
				while (loadedResources[i].resource->Release()) { }
				i++;
			}
			loadedResources.Clear();
		}
		#pragma endregion

		#pragma region Member - Load
		IResource* ContentManagerModule::Load(PInt hash, wstring name)
		{
			name = HelperPath::GetResourcePath(hash, name);
			IResource* value = this->findLoadedResource(hash, name);

			if (value == 0)
			{
				bool loadFile = true;

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
					throw "Not supported";
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

					if (loadFile) value->LoadFromFile(name.c_str());
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
				(IShader*)this->Load(typeid(IShader).hash_code(), name)
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

		#pragma region Private Member - Debug - DynamicReload
		void ContentManagerModule::initThread()
		{
			DllMain::Module->threadDynamicReload();
		}

		void ContentManagerModule::threadDynamicReload()
		{
			wstring filePath = HelperPath::CombineWorkingPath(L"Data");
			HANDLE hDir = CreateFile(
				filePath.c_str(),
				FILE_LIST_DIRECTORY,                
				FILE_SHARE_READ | FILE_SHARE_DELETE,
				NULL,                               
				OPEN_EXISTING,                      
				FILE_FLAG_BACKUP_SEMANTICS,         
				NULL                                
			);

			DWORD returnSize;
			FILE_NOTIFY_INFORMATION infos[1024];

			while (ReadDirectoryChangesW(hDir, &infos, sizeof(infos), TRUE, FILE_NOTIFY_CHANGE_LAST_WRITE, &returnSize, 0, 0))
			{
				EnterCriticalSection(&threadCriticle);

				Byte* dataBin = (Byte*)infos;
				FILE_NOTIFY_INFORMATION* dataInfo = infos;

				do 
				{
					wstring fileName = HelperPath::Combine(
						filePath,
						wstring(dataInfo->FileName, dataInfo->FileNameLength / sizeof(wchar_t))
					);

					HANDLE handle;
					while((handle = CreateFile(fileName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) { }
					CloseHandle(handle);

					changedFiles.Add(fileName);

					dataBin += dataInfo->NextEntryOffset;
					dataInfo = (FILE_NOTIFY_INFORMATION*)dataBin;
				} 
				while (dataInfo->NextEntryOffset);

				LeaveCriticalSection(&threadCriticle);
			}
		}
		#pragma endregion
	}
}
