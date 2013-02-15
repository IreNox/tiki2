
#include "Core/TypeGlobals.h"
#include "Core/HelperLog.h"
#include "Core/HelperPath.h"

#include "Core/Engine.h"
#include "Core/LibraryManager.h"

#include "Core/FileStream.h"
#include "Core/MemoryStream.h"
#include "Core/CompressedStream.h"

#include "ContentManager/ContentManagerModule.h"
#include "ContentManager/DllMain.h"

#include <typeinfo.h>

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		ContentManagerModule::ContentManagerModule(Engine* engine)
			: IContentManager(engine), loadedResources(), disposing(false), resourceContext(0)
		{
		}

		ContentManagerModule::~ContentManagerModule()
		{
		}
		#pragma endregion

		#pragma region Member
		void ContentManagerModule::ReleaseResource(IResource* res)
		{
			if (disposing) return;

			UInt32 i = 0;
			while (i < loadedResources.Count())
			{
				if (loadedResources[i].resource == res)
				{
					loadedResources.RemoveAt(i);
					return;
				}

				i++;
			}
		}
		#pragma endregion

		#pragma region Member - Module
		bool ContentManagerModule::Initialize(EngineDescription& desc)
		{
			#if _DEBUG
			InitializeCriticalSection(&threadCriticle);

			filePath = engine->HPath.CombineWorkingPath(L"Data");

			threadHandle = CreateThread(
				0,
				2000,
				(LPTHREAD_START_ROUTINE)initThread,
				0,
				THREAD_TERMINATE,
				&threadId
			);
			#endif

			if (engine->HPath.FileExists(L"Data/TikiRes.tikipak"))
			{
				FileStream* stream = TIKI_NEW FileStream(L"Data/TikiRes.tikipak", FM_Read);
				//CompressedStream* stream = TIKI_NEW CompressedStream(L"Data/TikiRes.tikipak", COM_Read);
				resourceContext = TIKI_NEW ResIOContext(stream, false);

				wchar_t* filelist = (wchar_t*)resourceContext->ReadPartPointer(resourceContext->GetHeader()->FilelistId);
				UInt32* datalist = (UInt32*)resourceContext->ReadPartPointer(resourceContext->GetHeader()->DatalistId);

				UInt32 i = 0;
				UInt32 pos = 0;
				while (i < resourceContext->GetHeader()->FileCount)
				{
					resourcePackage.Add(filelist + pos, datalist[i]);

					pos += (UInt32)wcslen(filelist + pos) + 1;
					i++;
				}
				resourcePackage.MarkAsOptimized();
			}

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
								changedFiles[i].CStr()
							);
						}
						catch (const char*)
						{
							engine->HLog.Write("Can't reload Resource");
						}
						catch (const wchar_t*)
						{
							engine->HLog.Write("Can't reload Resource");
						}
						catch (wstring)
						{
							engine->HLog.Write("Can't reload Resource");
						}
						catch (string s)
						{
							engine->HLog.Write("Can't reload Resource. Error: " + s);
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

			disposing = true;

			UInt32 i = 0;
			while (i < loadedResources.Count())
			{
				loadedResources[i].resource->Release();
				i++;
			}
			loadedResources.Clear();

			SafeDelete(&resourceContext);
		}
		#pragma endregion

		#pragma region Member - Load
		IResource* ContentManagerModule::Load(PInt hash, wstring name)
		{
			name = engine->librarys->GetResourcePath(hash, name);
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
					value = TIKI_NEW Mesh(engine);
				}
				else if (hash == typeid(IModel).hash_code())
				{
					value = engine->librarys->CreateResource<IModel>();
				}
				else if (hash == typeid(ISound).hash_code())
				{
					value = engine->librarys->CreateResource<ISound>();
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

					if (loadFile)
					{
						Stream* stream = this->LoadData(name);

						if (stream == 0)
						{
#if _DEBUG
							engine->HLog.Write("Can't Load Resource: " + StringWtoA(name));
#endif

							return 0;
						}
						stream->AddRef();

						try
						{
							value->LoadFromStream(name.CStr(), stream);
						}
						catch (string e)
						{							
							MessageBoxA(0, e.CStr(), "TikiEngine 2.0", MB_OK | MB_ICONERROR);
						}

						SafeRelease(&stream);
					}
				}
			}
			
			return value;
		}
		#pragma endregion

		#pragma region Member - LoadData
		Stream* ContentManagerModule::LoadData(wstring name)
		{
			engine->HPath.CheckSlashes(name);

			UInt32 id = 0;
			Stream* stream = 0;
			if (resourcePackage.TryGetValue(name, &id))
			{
				stream = TIKI_NEW MemoryStream(
					resourceContext->ReadPartPointer(id),
					resourceContext->ReadPart(id).ArrayCount
				);
			}
			else
			{
				FileStream* fileStream = TIKI_NEW FileStream(name, FM_Read);

				if (fileStream->IsOpen())
					stream = fileStream;
			}

			return stream;
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

		ISound* ContentManagerModule::LoadSound(const wstring& name)
		{
			return (ISound*)this->Load(
				typeid(ISound).hash_code(),
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
			Material* mat = TIKI_NEW Material(engine);
			mat->SetShader(
				(IShader*)this->Load(typeid(IShader).hash_code(), name)
			);

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
					if (hash == typeid(IModel).hash_code())
					{
						IModel* model = engine->librarys->CreateResource<IModel>();
						model->CreateInstance(
							(IModel*)loadedResources[i].resource
						);

						return model;
					}
					else
					{
						return loadedResources[i].resource;
					}
				}

				i++;
			}

			return 0;
		}
		#pragma endregion

		#pragma region Private Member - Debug - DynamicReload
		#if _DEBUG
		void ContentManagerModule::initThread()
		{
			DllMain::Module->threadDynamicReload();
		}

		void ContentManagerModule::threadDynamicReload()
		{
			HANDLE hDir = CreateFile(
				filePath.CStr(),
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
					wstring fileName = engine->HPath.Combine(
						filePath,
						wstring(dataInfo->FileName, dataInfo->FileNameLength / sizeof(wchar_t))
					);

					UInt32 len = (UInt32)engine->HPath.GetWorkingPath().Length() + 1;
					fileName = fileName.Substring(len, fileName.Length() - len);

					if (engine->HPath.FileExists(fileName))
					{
						UInt32 counter = 0;

						HANDLE handle = 0;
						while((handle = CreateFile(fileName.CStr(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE && counter < 1000) { counter++; }
						CloseHandle(handle);

						if (counter < 1000)
							changedFiles.Add(fileName);
					}

					dataBin += dataInfo->NextEntryOffset;
					dataInfo = (FILE_NOTIFY_INFORMATION*)dataBin;
				} 
				while (dataInfo->NextEntryOffset);

				LeaveCriticalSection(&threadCriticle);
			}
		}
		#endif
		#pragma endregion
	}
}
