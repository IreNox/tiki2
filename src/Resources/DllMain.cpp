
#include "Resources/DllMain.h"

#include <typeinfo.h>

namespace TikiEngine
{
	using namespace TikiEngine::Resources;
	using namespace TikiEngine::Components;

	TikiInfo DllMain::DllInfo = TikiInfo();

	Engine* DllMain::Engine = 0;
	ContentManagerModule* DllMain::ModuleGraphics = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::ModuleGraphics = new ContentManagerModule(engine);

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiResource = CreateResource;
		DllInfo.FuncTikiComponent = CreateComponent;

		DllInfo.Modules.Add(typeid(IContentManager).hash_code());
	}

	IModule* DllMain::CreateModule(IntPtr hash)
	{
		if (hash != typeid(IContentManager).hash_code())
		{
			return 0;
		}

		return DllMain::ModuleGraphics;
	}

	IResource* DllMain::CreateResource(IntPtr hash)
	{
		return 0;
	}

	Component* DllMain::CreateComponent(IntPtr hash, GameObject* gameObject)
	{
		return 0;
	}
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine)
{
	TikiEngine::DllMain::InitDll(engine);

	return &TikiEngine::DllMain::DllInfo;
}