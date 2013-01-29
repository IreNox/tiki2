#pragma once

#include "Core/TikiInfo.h"
#include "Core/Dictionary.h"

#include "Sound/SoundModule.h"

using TikiEngine::Engine;
using TikiEngine::TikiInfo;

namespace TikiEngine
{
	using TikiEngine::Modules::IModule;
	using TikiEngine::Modules::SoundModule;
	using TikiEngine::Components::Component;

	class DllMain
	{
	public:

		static TikiInfo DllInfo;

		static Engine* Engine;
		static SoundModule* Module;

		static void InitDll(TikiEngine::Engine* engine);
		static void DisposeDll();

		static IModule* CreateModule(PInt);
		static IResource* CreateResource(PInt);
		static Component* CreateComponent(PInt, GameObject* gameObject);

		static wcstring GetResourceExt(PInt);
		static wcstring GetResourcePath(PInt);

	private:

		DllMain() {}
		~DllMain() {}
	};
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine);