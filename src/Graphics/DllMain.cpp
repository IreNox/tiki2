
#include "Graphics/DllMain.h"
#include <typeinfo.h>


#include "Graphics/MeshRenderer.h"

namespace TikiEngine
{
	using namespace TikiEngine::Graphics;
	using namespace TikiEngine::Components;

	TikiInfo DllMain::DllInfo = TikiInfo();
	
	Engine* DllMain::Engine = 0;
	ID3D11Device* DllMain::Device = 0;
	ID3D11DeviceContext* DllMain::Context = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiComponent = CreateComponent;
	}

	IModule* DllMain::CreateModule(IntPtr hash)
	{
		if (hash == typeid(IGraphics).hash_code())
		{
			return new Graphics(Engine);
		}

		return 0;
	}

	Component* DllMain::CreateComponent(IntPtr hash, GameObject* gameObject)
	{
		if (hash == typeid(IMeshRenderer).hash_code())
		{
			return new MeshRenderer(Engine, gameObject);
		}

		return 0;
	}
}

TikiInfo* GetTikiInfo(Engine* engine)
{
	TikiEngine::DllMain::InitDll(engine);

	return &TikiEngine::DllMain::DllInfo;
}