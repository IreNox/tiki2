
#include "Graphics/DllMain.h"

#include "Graphics/Font.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/Model.h"

#include "Graphics/MeshRenderer.h"
#include "Graphics/TerrainRenderer.h"

#include "Graphics/GraphicsModule.h"
#include "Graphics/SpriteBatchModule.h"

#include "Graphics/FbxLoader.h"

#include <typeinfo.h>

namespace TikiEngine
{
	using namespace TikiEngine::Components;

	TikiInfo DllMain::DllInfo = TikiInfo();
	
	Engine* DllMain::Engine = 0;
	FbxLoader* DllMain::FBXLoader = 0;

	GraphicsModule* DllMain::ModuleGraphics = 0;
	SpriteBatchModule* DllMain::ModuleSpriteBatch = 0;

	ID3D11Device* DllMain::Device = 0;
	ID3D11DeviceContext* DllMain::Context = 0;

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::FBXLoader = new FbxLoader(engine);
		DllMain::ModuleGraphics = new GraphicsModule(engine);
		DllMain::ModuleSpriteBatch = new SpriteBatchModule(engine);

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiResource = CreateResource;
		DllInfo.FuncTikiComponent = CreateComponent;
		DllInfo.FuncDispose = DisposeDll;

		DllInfo.Modules.Add(typeid(IGraphics).hash_code());
		DllInfo.Modules.Add(typeid(ISpriteBatch).hash_code());

		DllInfo.Resources.Add(typeid(IFont).hash_code());
		DllInfo.Resources.Add(typeid(IShader).hash_code());
		DllInfo.Resources.Add(typeid(ITexture).hash_code());
		DllInfo.Resources.Add(typeid(IRenderTarget).hash_code());
		DllInfo.Resources.Add(typeid(IModel).hash_code());

		DllInfo.Components.Add(typeid(IMeshRenderer).hash_code());
		DllInfo.Components.Add(typeid(ITerrainRenderer).hash_code());
	}

	void DllMain::DisposeDll()
	{
		SafeRelease(&DllMain::FBXLoader);
	}

	IModule* DllMain::CreateModule(PInt hash)
	{
		if (hash == typeid(IGraphics).hash_code())
		{
			return DllMain::ModuleGraphics;
		}
		else if (hash == typeid(ISpriteBatch).hash_code())
		{
			return DllMain::ModuleSpriteBatch;
		}

		return 0;
	}

	IResource* DllMain::CreateResource(PInt hash)
	{
		if (hash == typeid(IFont).hash_code())
		{
			return new Font(DllMain::Engine);
		}
		else if (hash == typeid(IShader).hash_code())
		{
			return new Shader(DllMain::Engine);
		}
		else if (hash == typeid(ITexture).hash_code())
		{
			return new Texture(DllMain::Engine);
		}
		else if (hash == typeid(IRenderTarget).hash_code())
		{
			return new RenderTarget(DllMain::Engine);
		}
		else if(hash == typeid(IModel).hash_code())
		{
			return new Model(DllMain::Engine);
		}
		return 0;
	}

	Component* DllMain::CreateComponent(PInt hash, GameObject* gameObject)
	{
		if (hash == typeid(IMeshRenderer).hash_code())
		{
			return new MeshRenderer(DllMain::Engine, gameObject);
		}
		else if (hash == typeid(ITerrainRenderer).hash_code())
		{
			return new TerrainRenderer(DllMain::Engine, gameObject);
		}

		return 0;
	}
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine)
{
	TikiEngine::DllMain::InitDll(engine);

	return &TikiEngine::DllMain::DllInfo;
}