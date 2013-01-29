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
	typedef wcstring(*FuncGetTikiResourcePath)(PInt);
	typedef wcstring(*FuncGetTikiResourceExt)(PInt);
	typedef void(*FuncDisposeLibrary)();

	struct TikiInfo 
	{
		HMODULE LibraryHandle;

		FuncGetTikiModule FuncTikiModule;
		FuncGetTikiResource FuncTikiResource;
		FuncGetTikiComponent FuncTikiComponent;

		FuncGetTikiResourceExt FuncTikiResourceExt;
		FuncGetTikiResourcePath FuncTikiResourcePath;

		FuncDisposeLibrary FuncDispose;

		List<PInt> Modules;
		List<PInt> Resources;
		List<PInt> Components;

		TikiInfo()
			: LibraryHandle(0), FuncTikiModule(0), FuncTikiResource(0), FuncTikiComponent(0), FuncDispose(0), FuncTikiResourcePath(0), FuncTikiResourceExt(0), Modules(), Resources(), Components()
		{
		}

		~TikiInfo()
		{
		}
	};
}

