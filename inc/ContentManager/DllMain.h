#pragma once

#include "Core/TikiInfo.h"
#include "Core/Dictionary.h"

#include "ContentManager/ContentManagerModule.h"

using TikiEngine::Engine;
using TikiEngine::TikiInfo;

namespace TikiEngine
{
	using TikiEngine::Modules::IModule;
	using TikiEngine::Resources::ContentManagerModule;
	using TikiEngine::Components::Component;

	class DllMain
	{
	public:

		static TikiInfo DllInfo;

		static Engine* Engine;
		static ContentManagerModule* Module;

		static void InitDll(TikiEngine::Engine* engine);

		static IModule* CreateModule(PInt);
		static IResource* CreateResource(PInt);
		static Component* CreateComponent(PInt, GameObject* gameObject);

	private:

		DllMain() {}
		~DllMain() {}
	};
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine);