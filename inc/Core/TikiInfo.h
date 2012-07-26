#pragma once

#include "Core/TypeInc.h"
#include "Core/List.h"

#include "Core/IModule.h"
#include "Core/Component.h"

namespace TikiEngine
{
	using namespace TikiEngine::Modules;
	using namespace TikiEngine::Components;

	typedef IModule*(*FuncGetTikiModule)(IntPtr);
	typedef Component*(*FuncGetTikiComponent)(IntPtr);

	struct TikiInfo 
	{
		wstring LibraryName;
		HMODULE LibraryHandle;

		FuncGetTikiModule FuncTikiModule;
		FuncGetTikiComponent FuncTikiComponent;

		List<IntPtr> Modules;
		List<IntPtr> Components;

		TikiInfo()
			: LibraryName(), LibraryHandle(0), FuncTikiModule(0), FuncTikiComponent(0), Modules(), Components()
		{
		}

		~TikiInfo()
		{
		}
	};
}

