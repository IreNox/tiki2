
#include "Core/LibraryManager.h"
#include "Core/TikiPerformanceCounter.h"

#include "Core/Mesh.h"

namespace TikiEngine
{
	namespace Modules
	{
		typedef TikiInfo*(*GetTikiInfo)(Engine* engine);

		#pragma region Class
		LibraryManager::LibraryManager(Engine* engine)
			: IModule(engine), defaultLibrarys(), loadedLibrarys()
		{
		}

		LibraryManager::~LibraryManager()
		{
		}
		#pragma endregion

		#pragma region Init/Dispose
		bool LibraryManager::Initialize(EngineDescription& desc)
		{
			wstring path = engine->HPath.GetBinaryPath() + L"\\*.dll";

			WIN32_FIND_DATA file;
			HANDLE handle = FindFirstFile(path.CStr(), &file);

			if(handle != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (file.cFileName[0] == '.') continue;

					wstring fileName = file.cFileName;
					fileName = fileName.ToLower();

					if (fileName.StartsWith(L"tikiengine") && !desc.IgnoreModules.Contains(fileName))
					{
						loadLibrary(
							engine,
							engine->HPath.GetBinaryPath() + L"\\" + fileName
						);
					}
				}
				while (FindNextFile(handle, &file));
			}
			else
			{
				return false;
			}

			defaultLibrarys.Optimize();

			return true;
		}
		
		TikiInfo* LibraryManager::loadLibrary(Engine* engine, wstring libraryName)
		{
			if (loadedLibrarys.ContainsKey(libraryName))
			{
				return loadedLibrarys.Get(libraryName);
			}

#if _DEBUG
			TikiPerformanceCounter time;
			time.Start();
#endif

			HMODULE libraryHandle = LoadLibrary(libraryName.CStr());
			if (libraryHandle == 0) return 0;

			FARPROC temp = GetProcAddress(libraryHandle, "GetTikiInfo");
			GetTikiInfo getTikiInfo = (GetTikiInfo)temp;
			if (getTikiInfo == 0)
			{
				FreeLibrary(libraryHandle);
				return 0;
			}

			TikiInfo* info = getTikiInfo(engine);
			if (info == 0)
			{
				FreeLibrary(libraryHandle);
				return 0;
			}

			info->LibraryHandle = libraryHandle;

			UInt32 i = 0;
			while (i < info->Modules.Count())
			{
				if (!defaultLibrarys.ContainsKey(info->Modules[i]))
				{
					defaultLibrarys.Add(info->Modules[i], info);
				}

				i++;
			}

			i = 0;
			while (i < info->Resources.Count())
			{
				if (!defaultLibrarys.ContainsKey(info->Resources[i]))
				{
					defaultLibrarys.Add(info->Resources[i], info);
				}

				i++;
			}

			i = 0;
			while (i < info->Components.Count())
			{
				if (!defaultLibrarys.ContainsKey(info->Components[i]))
				{
					defaultLibrarys.Add(info->Components[i], info);
				}

				i++;
			}

			loadedLibrarys.Add(libraryName, info);

#if _DEBUG
			double el = time.Stop();

			engine->HLog.Write(
				"LoadLibrary: " + StringWtoA(engine->HPath.GetFilename(libraryName)) + " - ElapsedTime: " + StringConvert::ToString(el) + " sec"
				);
#endif

			return info;
		}

		void LibraryManager::Dispose()
		{
			List<TikiInfo*>* infos = loadedLibrarys.GetValues();

			UInt32 i = 0;			
			TikiInfo* info = 0;

			while (i < infos->Count())
			{
				info = infos->Get(i);

				if (info->FuncDispose != 0)
				{
					info->FuncDispose();
				}

				FreeLibrary(info->LibraryHandle);

				i++;
			}

			delete(infos);
		}

#pragma endregion

		#pragma region Begin/End
		void LibraryManager::Begin()
		{
		}

		void LibraryManager::End()
		{
		}
		#pragma endregion

		#pragma region Member - Resource
		wstring LibraryManager::GetResourcePath(PInt typeHash, const wstring& fileName) const
		{
			TikiInfo* info = 0;
			wstring typeExt = L"";
			wstring typeName = L"";

			if (defaultLibrarys.TryGetValue(typeHash, &info))
			{
				typeExt = info->FuncTikiResourceExt(typeHash);
				typeName = info->FuncTikiResourcePath(typeHash);
			}
			else if (typeid(Mesh).hash_code() == typeHash)
			{
				typeExt = L"obj";
				typeName = L"Meshes";
			}

			return engine->HPath.Combine(
				L"Data/" + typeName,
				fileName + L"." + typeExt
			);
		}
		#pragma endregion
	}
}