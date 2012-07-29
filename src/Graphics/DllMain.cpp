
#include "Graphics/DllMain.h"
#include "Graphics/MeshRenderer.h"

#include <typeinfo.h>

namespace TikiEngine
{
	using namespace TikiEngine::Graphics;
	using namespace TikiEngine::Components;

	TikiInfo DllMain::DllInfo = TikiInfo();
	
	Engine* DllMain::Engine = 0;

	GraphicsModule* DllMain::Module = 0;
	ID3D11Device* DllMain::Device = 0;
	ID3D11DeviceContext* DllMain::Context = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::Module = new GraphicsModule(engine);

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiComponent = CreateComponent;

		DllInfo.Modules.Add(typeid(IGraphics).hash_code());

		DllInfo.Components.Add(typeid(IMeshRenderer).hash_code());
	}

	IModule* DllMain::CreateModule(IntPtr hash)
	{
		if (hash != typeid(IGraphics).hash_code())
		{
			return 0;
		}

		return DllMain::Module;
	}

	Component* DllMain::CreateComponent(IntPtr hash, GameObject* gameObject)
	{
		if (hash == typeid(IMeshRenderer).hash_code())
		{
			return new MeshRenderer(DllMain::Engine, gameObject);
		}

		return 0;
	}
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine)
{
	TikiEngine::DllMain::InitDll(engine);

	return &TikiEngine::DllMain::DllInfo;
}