
#include "Core/HelperLibrary.h"
#include <direct.h>

namespace TikiEngine
{
	typedef TikiInfo*(*GetTikiInfo)(Engine* engine);

	Dictionary<IntPtr, TikiInfo*> HelperLibrary::defaultLibrarys = Dictionary<IntPtr, TikiInfo*>();
	Dictionary<wstring, TikiInfo*> HelperLibrary::loadedLibrarys = Dictionary<wstring, TikiInfo*>();

	void HelperLibrary::LoadDefault(Engine* engine)
	{
		WCHAR cd[MAX_PATH];

		_wgetcwd(cd, MAX_PATH);
		wstring path = wstring(cd) + L"*.dll";

		WIN32_FIND_DATA file;
		HANDLE handle = FindFirstFile(path.c_str(), &file);

		if(handle != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (file.cFileName[0] == '.') continue;

				TikiInfo* info = loadLibrary(engine, wstring(file.cFileName));

				if (info != 0)
				{
					for (int i = 0; i < info->Modules.Count(); i++)
					{
						if (!defaultLibrarys.ContainsKey(info->Modules[i]))
						{
							defaultLibrarys.Add(info->Modules[i], info);
						}
					}

					for (int i = 0; i < info->Components.Count(); i++)
					{
						if (!defaultLibrarys.ContainsKey(info->Components[i]))
						{
							defaultLibrarys.Add(info->Components[i], info);
						}
					}
				}
			}
			while (FindNextFile(handle, &file));
		}
	}

	TikiInfo* HelperLibrary::loadLibrary(Engine* engine, wstring libraryName)
	{
		if (loadedLibrarys.ContainsKey(libraryName))
		{
			return loadedLibrarys.Get(libraryName);
		}

		HMODULE libraryHandle = LoadLibrary(libraryName.c_str());
		if (libraryHandle == 0) return 0;

		GetTikiInfo getTikiInfo = (GetTikiInfo)GetProcAddress(libraryHandle, "GetTikiInfo");
		if (getTikiInfo == 0) return 0;

		TikiInfo* info = getTikiInfo(engine);
		if (info == 0) return 0;

		info->LibraryName = libraryName;
		info->LibraryHandle = libraryHandle;

		loadedLibrarys.Add(libraryName, info);

		return info;
	}
}