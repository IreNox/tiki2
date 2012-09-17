
#include "Sound/DllMain.h"

#include "Sound/Sound.h"

#include <typeinfo.h>

namespace TikiEngine
{
	using namespace TikiEngine::Resources;
	using namespace TikiEngine::Components;

	TikiInfo DllMain::DllInfo = TikiInfo();

	Engine* DllMain::Engine = 0;
	SoundModule* DllMain::Module = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::Module = new SoundModule(engine);

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiResource = CreateResource;
		DllInfo.FuncTikiComponent = CreateComponent;

		DllInfo.Modules.Add(typeid(ISoundSystem).hash_code());

		DllInfo.Resources.Add(typeid(ISound).hash_code());
	}

	IModule* DllMain::CreateModule(IntPtr hash)
	{
		if (hash != typeid(ISoundSystem).hash_code())
		{
			return 0;
		}

		return DllMain::Module;
	}

	IResource* DllMain::CreateResource(IntPtr hash)
	{
		if (hash == typeid(ISound).hash_code())
		{
			return new Sound(DllMain::Engine);
		}

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