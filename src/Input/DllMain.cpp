
#include "Input/DllMain.h"

#include <typeinfo.h>

namespace TikiEngine
{
	using namespace TikiEngine::Modules;

	TikiInfo DllMain::DllInfo = TikiInfo();
	
	Engine* DllMain::Engine = 0;
	InputModule* DllMain::ModuleGraphics = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::ModuleGraphics = new InputModule(engine);

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiComponent = CreateComponent;

		DllInfo.Modules.Add(typeid(IInput).hash_code());
	}

	IModule* DllMain::CreateModule(PInt hash)
	{
		if (hash != typeid(IInput).hash_code())
		{
			return 0;
		}

		return DllMain::ModuleGraphics;
	}

	Component* DllMain::CreateComponent(PInt hash, GameObject* gameObject)
	{
		return 0;
	}
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine)
{
	TikiEngine::DllMain::InitDll(engine);

	return &TikiEngine::DllMain::DllInfo;
}