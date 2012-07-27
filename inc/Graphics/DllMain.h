#pragma once

#include "Core/TikiInfo.h"
#include "Core/Dictionary.h"

#include "Graphics/Graphics.h"

#include "D3D11.h"
#include "D3DX11.h"

using TikiEngine::Engine;
using TikiEngine::TikiInfo;

namespace TikiEngine
{
	using TikiEngine::Modules::IModule;
	using TikiEngine::Components::Component;

	class DllMain
	{
	public:

		static TikiInfo DllInfo;

		static Engine* Engine;

		static Graphics Graphics;
		static ID3D11Device* Device;
		static ID3D11DeviceContext* Context;

		static void InitDll(TikiEngine::Engine* engine);

		static IModule* CreateModule(IntPtr);
		static Component* CreateComponent(IntPtr, GameObject* gameObject);

	private:

		DllMain() {}
		~DllMain() {}
	};
}

TikiInfo* GetTikiInfo(Engine* engine);