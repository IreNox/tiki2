
#include "Physics/DllMain.h"
#include "Physics/BoxCollider.h"
#include "Physics/PhysicsMaterial.h"

#include <typeinfo.h>

namespace TikiEngine
{
	using namespace TikiEngine::Modules;
	using namespace TikiEngine::Components;
	using namespace TikiEngine::Physics;

	TikiInfo DllMain::DllInfo = TikiInfo();

	Engine* DllMain::Engine = 0;

	PhysicsModule* DllMain::Module = 0;
	NxScene* DllMain::Scene = 0;
	NxPhysicsSDK* DllMain::PhysicsSDK = 0;
	NxControllerManager* DllMain::ControllerManager = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::Module = new PhysicsModule(engine);

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiResource = CreateResource;
		DllInfo.FuncTikiComponent = CreateComponent;

		DllInfo.Modules.Add(typeid(IPhysics).hash_code());

		DllInfo.Resources.Add(typeid(IPhysicsMaterial).hash_code());

		//DllInfo.Components.Add(typeid(ICollider).hash_code());
		DllInfo.Components.Add(typeid(IBoxCollider).hash_code());

		
	}

	IModule* DllMain::CreateModule(IntPtr hash)
	{
		if (hash != typeid(IPhysics).hash_code())
		{
			return 0;
		}

		return DllMain::Module;
	}

	IResource* DllMain::CreateResource(IntPtr hash)
	{
		if (hash == typeid(IPhysicsMaterial).hash_code())
		{
			return new PhysicsMaterial(DllMain::Engine);
		}

		return 0;
	}


	Component* DllMain::CreateComponent(IntPtr hash, GameObject* gameObject)
	{
		if (hash == typeid(IBoxCollider).hash_code())
		{
			return new BoxCollider(DllMain::Engine, gameObject);
		}

		return 0;
	}
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine)
{
	TikiEngine::DllMain::InitDll(engine);

	return &TikiEngine::DllMain::DllInfo;
}