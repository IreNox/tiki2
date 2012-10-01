#pragma once

#include "Core/TikiInfo.h"
#include "Core/Dictionary.h"

#include "D3D11.h"
#include "D3DX11.h"

using TikiEngine::Engine;
using TikiEngine::TikiInfo;

namespace TikiEngine
{
	namespace Resources
	{
		class FbxLoader;
	}
	
	namespace Modules
	{
		class GraphicsModule;
		class SpriteBatchModule;
	}

	using TikiEngine::Modules::IModule;
	using TikiEngine::Modules::GraphicsModule;
	using TikiEngine::Modules::SpriteBatchModule;
	using TikiEngine::Components::Component;


	using namespace TikiEngine::Resources;

	class DllMain
	{
	public:

		static TikiInfo DllInfo;

		static Engine* Engine;

		static FbxLoader* FBXLoader;

		static GraphicsModule* ModuleGraphics;
		static SpriteBatchModule* ModuleSpriteBatch;

		static ID3D11Device* Device;
		static ID3D11DeviceContext* Context;

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