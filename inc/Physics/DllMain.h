#pragma once

#include "Core/TikiInfo.h"
#include "Core/Dictionary.h"

#include "Physics/PhysicsModule.h"

using TikiEngine::Engine;
using TikiEngine::TikiInfo;

namespace TikiEngine
{
	using TikiEngine::Modules::IModule;
	using TikiEngine::Modules::PhysicsModule;
	using TikiEngine::Components::Component;

	class DllMain
	{
	public:

		static TikiInfo DllInfo;

		static Engine* Engine;

		static PhysicsModule* Module;
	    static NxScene* Scene;
		static NxPhysicsSDK* PhysicsSDK;
		static NxCookingInterface* Cooking;
		static NxControllerManager* ControllerManager;

		static void InitDll(TikiEngine::Engine* engine);
		static void DisposeDll();

		static IModule* CreateModule(PInt);
		static IResource* CreateResource(PInt);
		static Component* CreateComponent(PInt, GameObject* gameObject);

	private:

		DllMain() {}
		~DllMain() {}
	};
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine);