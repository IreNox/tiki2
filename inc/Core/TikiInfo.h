#pragma once

#include "Core/TypeInc.h"
#include "Core/List.h"

#include "Core/IModule.h"
#include "Core/Resource.h"
#include "Core/Component.h"

namespace TikiEngine
{
	using namespace TikiEngine::Modules;
	using namespace TikiEngine::Resources;
	using namespace TikiEngine::Components;

	typedef IModule*(*FuncGetTikiModule)(IntPtr);
	typedef Resource*(*FuncGetTikiResource)(IntPtr);
	typedef Component*(*FuncGetTikiComponent)(IntPtr, GameObject* gameObject);

	struct TikiInfo 
	{
		HMODULE LibraryHandle;

		FuncGetTikiModule FuncTikiModule;
		FuncGetTikiResource FuncTikiResource;
		FuncGetTikiComponent FuncTikiComponent;

		List<IntPtr> Modules;
		List<IntPtr> Resources;
		List<IntPtr> Components;

		TikiInfo()
			: LibraryHandle(0), FuncTikiModule(0), FuncTikiResource(0), FuncTikiComponent(0), Modules(), Resources(), Components()
		{
		}

		~TikiInfo()
		{
		}
	};
}

