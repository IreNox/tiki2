
#include "Physics/DllMain.h"
#include "Physics/BoxCollider.h"
#include "Physics/SphereCollider.h"
#include "Physics/PhysicsMaterial.h"
#include "Physics/CharacterController.h"
#include "Physics/BoundingBox.h"

#include <typeinfo.h>

namespace TikiEngine
{
	using namespace TikiEngine::Modules;
	using namespace TikiEngine::Components;
	using namespace TikiEngine::Physics;

	TikiInfo DllMain::DllInfo = TikiInfo();

	Engine* DllMain::Engine = 0;

	PhysicsModule* DllMain::ModuleGraphics = 0;
	NxScene* DllMain::Scene = 0;
	NxPhysicsSDK* DllMain::PhysicsSDK = 0;
	NxControllerManager* DllMain::ControllerManager = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::ModuleGraphics = new PhysicsModule(engine);

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiResource = CreateResource;
		DllInfo.FuncTikiComponent = CreateComponent;

		DllInfo.Modules.Add(typeid(IPhysics).hash_code());

		DllInfo.Resources.Add(typeid(IPhysicsMaterial).hash_code());
		DllInfo.Resources.Add(typeid(IBoundingBox).hash_code());

		DllInfo.Components.Add(typeid(IBoxCollider).hash_code());
		DllInfo.Components.Add(typeid(ISphereCollider).hash_code());
		DllInfo.Components.Add(typeid(ICharacterController).hash_code());

		
	}

	IModule* DllMain::CreateModule(PInt hash)
	{
		if (hash != typeid(IPhysics).hash_code())
		{
			return 0;
		}

		return DllMain::ModuleGraphics;
	}

	IResource* DllMain::CreateResource(PInt hash)
	{
		if (hash == typeid(IPhysicsMaterial).hash_code())
		{
			return new PhysicsMaterial(DllMain::Engine);
		}
		else if (hash == typeid(IBoundingBox).hash_code())
		{
			return new BoundingBox(DllMain::Engine);
		}


		return 0;
	}


	Component* DllMain::CreateComponent(PInt hash, GameObject* gameObject)
	{
		if (hash == typeid(IBoxCollider).hash_code())
		{
			return new BoxCollider(DllMain::Engine, gameObject);
		}
		else if (hash == typeid(ISphereCollider).hash_code())
		{
			return new SphereCollider(DllMain::Engine, gameObject);
		}
		else if (hash == typeid(ICharacterController).hash_code())
		{
			return new CharacterController(DllMain::Engine, gameObject);
		}

		return 0;
	}
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine)
{
	TikiEngine::DllMain::InitDll(engine);

	return &TikiEngine::DllMain::DllInfo;
}