
#include "Graphics/DllMain.h"

namespace TikiEngine
{
	TikiInfo DllMain::DllInfo = TikiInfo();
	
	ID3D11Device* DllMain::Device = 0;
	ID3D11DeviceContext* DllMain::Context = 0;

	void DllMain::InitDll()
	{
		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiComponent = CreateComponent;
	}

	IModule* DllMain::CreateModule(IntPtr hash)
	{

	}

	Component* DllMain::CreateComponent(IntPtr hash)
	{

	}
}

