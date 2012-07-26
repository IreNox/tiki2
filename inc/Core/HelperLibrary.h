#pragma once

#include "Core/TypeInc.h"
#include "Core/TikiInfo.h"

#include <Windows.h>
#include <typeinfo.h>

#include "Core/Dictionary.h"

namespace TikiEngine
{
	using namespace TikiEngine::Modules;
	using namespace TikiEngine::Components;

	class HelperLibrary
	{
	public:

		static void LoadDefault();

		#pragma region Member - Create
		template <class T>
		static T* CreateModule()
		{
			IntPtr hash;
			TikiInfo* info = getDefault<T>(&hash);

			if (info != 0)
			{
				return (T*)info->FuncTikiModule(hash);
			}

			return 0;
		}

		template <class T>
		static T* CreateComponent()
		{
			IntPtr hash;
			TikiInfo* info = getDefault<T>(&hash);

			if (info != 0)
			{
				return (T*)info->FuncTikiComponent(hash);
			}

			return 0;
		}
		#pragma endregion
		
	private:

		HelperLibrary();
		~HelperLibrary();

		static TikiInfo* loadLibrary(wstring libraryName);

		template <class T>
		static TikiInfo* getDefault(IntPtr* hash)
		{
			*hash = typeid(T).hash_code();

			if (defaultLibrarys.ContainsKey(*hash))
			{
				return defaultLibrarys.Get(*hash);
			}

			return 0;
		}

		static Dictionary<IntPtr, TikiInfo*> defaultLibrarys;
		static Dictionary<wstring, TikiInfo*> loadedLibrarys;
	};
}