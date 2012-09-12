#pragma once

#include "Core/TypeInc.h"
#include "Core/TikiInfo.h"
#include "Core/IModule.h"

#include <typeinfo.h>

#include "Core/Dictionary.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Components;

		class LibraryManager : public IModule
		{
		public:

			LibraryManager(Engine* engine);
			~LibraryManager();

			bool Initialize(EngineDescription& desc);

			void Begin();
			void End();

			void Dispose();

			#pragma region Member - Create
			template <class T>
			T* CreateModule()
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
			T* CreateResource()
			{
				IntPtr hash;
				TikiInfo* info = getDefault<T>(&hash);

				if (info != 0)
				{
					return (T*)info->FuncTikiResource(hash);
				}

				return 0;
			}

			template <class T>
			T* CreateComponent(GameObject* gameObject)
			{
				IntPtr hash;
				TikiInfo* info = getDefault<T>(&hash);
				T* comp = 0;

				if (info != 0)
				{
					comp = (T*)info->FuncTikiComponent(hash, gameObject);
				}

				if (comp != 0)
				{
					gameObject->AddComponent(comp);
				}

				return 0;
			}
			#pragma endregion

		private:

			Dictionary<IntPtr, TikiInfo*> defaultLibrarys;
			Dictionary<wstring, TikiInfo*> loadedLibrarys;

			TikiInfo* loadLibrary(Engine* engine, wstring libraryName);

			template <class T>
			TikiInfo* getDefault(IntPtr* hash)
			{
				*hash = typeid(T).hash_code();

				if (defaultLibrarys.ContainsKey(*hash))
				{
					return defaultLibrarys.Get(*hash);
				}

				return 0;
			}
		};
	}
}