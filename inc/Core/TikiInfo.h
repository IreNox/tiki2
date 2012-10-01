#pragma once

#include "Core/TypeDef.h"
#include "Core/List.h"

#include "Core/IModule.h"
#include "Core/IResource.h"
#include "Core/Component.h"

namespace TikiEngine
{
	using namespace TikiEngine::Modules;
	using namespace TikiEngine::Resources;
	using namespace TikiEngine::Components;

	typedef IModule*(*FuncGetTikiModule)(PInt);
	typedef IResource*(*FuncGetTikiResource)(PInt);
	typedef Component*(*FuncGetTikiComponent)(PInt, GameObject* gameObject);
	typedef void(*FuncDisposeLibrary)();

	struct TikiInfo 
	{
		HMODULE LibraryHandle;

		FuncGetTikiModule FuncTikiModule;
		FuncGetTikiResource FuncTikiResource;
		FuncGetTikiComponent FuncTikiComponent;

		FuncDisposeLibrary FuncDispose;

		List<PInt> Modules;
		List<PInt> Resources;
		List<PInt> Components;

		TikiInfo()
			: LibraryHandle(0), FuncTikiModule(0), FuncTikiResource(0), FuncTikiComponent(0), FuncDispose(0), Modules(), Resources(), Components()
		{
		}

		~TikiInfo()
		{
		}
	};
}

