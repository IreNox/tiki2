
#include "Physics/DllMain.h"
#include "Core/ICollider.h"

#include <typeinfo.h>

namespace TikiEngine
{
	using namespace TikiEngine::Modules;
	using namespace TikiEngine::Components;

	TikiInfo DllMain::DllInfo = TikiInfo();

	Engine* DllMain::Engine = 0;

	PhysicsModule* DllMain::Module = 0;
  NxScene* DllMain::Scene = 0;
  NxPhysicsSDK* DllMain::PhysicsSDK = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::Module = new PhysicsModule(engine);

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiComponent = CreateComponent;

		DllInfo.Modules.Add(typeid(IPhysics).hash_code());

		DllInfo.Components.Add(typeid(ICollider).hash_code());
	}

	IModule* DllMain::CreateModule(IntPtr hash)
	{
		if (hash != typeid(IPhysics).hash_code())
		{
			return 0;
		}

		return DllMain::Module;
	}

	Component* DllMain::CreateComponent(IntPtr hash, GameObject* gameObject)
	{
		if (hash == typeid(ICollider).hash_code())
		{
			//return new MeshRenderer(DllMain::Engine, gameObject);
		}

		return 0;
	}
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine)
{
	TikiEngine::DllMain::InitDll(engine);

	return &TikiEngine::DllMain::DllInfo;
}