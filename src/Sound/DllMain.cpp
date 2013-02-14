
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
		DllMain::Module = TIKI_NEW SoundModule(engine);
		DllMain::Module->AddRef();

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiResource = CreateResource;
		DllInfo.FuncTikiComponent = CreateComponent;
		DllInfo.FuncTikiResourceExt = GetResourceExt;
		DllInfo.FuncTikiResourcePath = GetResourcePath;
		DllInfo.FuncDispose = DisposeDll;
		
		DllInfo.Modules.Add(typeid(ISoundSystem).hash_code());

		DllInfo.Resources.Add(typeid(ISound).hash_code());
	}

	void DllMain::DisposeDll()
	{
		SafeRelease(&DllMain::Module);
	}

	IModule* DllMain::CreateModule(PInt hash)
	{
		if (hash != typeid(ISoundSystem).hash_code())
		{
			return 0;
		}

		return DllMain::Module;
	}

	IResource* DllMain::CreateResource(PInt hash)
	{
		if (hash == typeid(ISound).hash_code())
		{
			return TIKI_NEW Sound(DllMain::Engine);
		}

		return 0;
	}

	wcstring DllMain::GetResourceExt(PInt hash)
	{
		if (hash == typeid(ISound).hash_code())
		{
			return L"wav";
		}

		return 0;
	}

	wcstring DllMain::GetResourcePath(PInt hash)
	{
		if (hash == typeid(ISound).hash_code())
		{
			return L"sounds";
		}

		return 0;
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