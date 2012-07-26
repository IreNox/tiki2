#pragma once

#include "Core/TikiInfo.h"
#include "Core/Dictionary.h"

#include "D3D11.h"
#include "D3DX11.h"

namespace TikiEngine
{
	using TikiEngine::Modules::IModule;
	using TikiEngine::Components::Component;

	class DllMain
	{
	public:

		static TikiInfo DllInfo;

		static ID3D11Device* Device;
		static ID3D11DeviceContext* Context;

		static void InitDll();

		static IModule* CreateModule(IntPtr);
		static Component* CreateComponent(IntPtr);

	private:

		DllMain() {}
		~DllMain() {}

		//static Dictionary<UInt64, 
	};
}

