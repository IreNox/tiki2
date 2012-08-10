
#include "Core/LibraryManager.h"
#include <direct.h>

namespace TikiEngine
{
	namespace Modules
	{
		typedef TikiInfo*(*GetTikiInfo)(Engine* engine);

		LibraryManager::LibraryManager(Engine* engine)
			: IModule(engine), defaultLibrarys(), loadedLibrarys()
		{
		}

		LibraryManager::~LibraryManager()
		{
		}

		bool LibraryManager::Initialize(EngineDescription& desc)
		{
			WCHAR cd[MAX_PATH];

			_wgetcwd(cd, MAX_PATH);
			wstring path = wstring(cd) + L"\\*.dll";

			WIN32_FIND_DATA file;
			HANDLE handle = FindFirstFile(path.c_str(), &file);

			if(handle != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (file.cFileName[0] == '.') continue;

					loadLibrary(
						engine,
						wstring(cd) + L"\\" + wstring(file.cFileName)
					);
				}
				while (FindNextFile(handle, &file));
			}
			else
			{
				return false;
			}

			return true;
		}

		void LibraryManager::Begin()
		{
		}

		void LibraryManager::End()
		{
		}

		void LibraryManager::Dispose()
		{
			List<TikiInfo*> infos = loadedLibrarys.GetValues();

			UInt32 i = 0;			
			TikiInfo* info = 0;

			while (i < infos.Count())
			{
				info = infos[i];

				FreeLibrary(info->LibraryHandle);

				i++;
			}
		}

		TikiInfo* LibraryManager::loadLibrary(Engine* engine, wstring libraryName)
		{
			if (loadedLibrarys.ContainsKey(libraryName))
			{
				return loadedLibrarys.Get(libraryName);
			}

			HMODULE libraryHandle = LoadLibrary(libraryName.c_str());
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

			return info;
		}
	}
}