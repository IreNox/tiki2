
#include "Input/DllMain.h"

namespace TikiEngine
{
	using namespace TikiEngine::Modules;

	TikiInfo DllMain::DllInfo = TikiInfo();
	
	Engine* DllMain::Engine = 0;
	InputModule* DllMain::ModuleInput = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::ModuleInput = TIKI_NEW InputModule(engine);
		DllMain::ModuleInput->AddRef();

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiComponent = CreateComponent;
		DllInfo.FuncDispose = DisposeDll;

		DllInfo.Modules.Add(typeid(IInput).hash_code());
	}

	void DllMain::DisposeDll()
	{
		SafeRelease(&DllMain::ModuleInput);
	}

	IModule* DllMain::CreateModule(PInt hash)
	{
		if (hash != typeid(IInput).hash_code())
		{
			return 0;
		}

		return DllMain::ModuleInput;
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