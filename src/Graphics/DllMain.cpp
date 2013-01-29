
#include "Graphics/DllMain.h"

#include "Graphics/Font.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

#include "Graphics/SpriteBatchModule.h"

#if TIKI_DX10 || TIKI_DX11
#include "Graphics/RenderTarget.h"
#include "Graphics/Model.h"
#include "Graphics/TikiAnimation.h"

#include "Graphics/MeshRenderer.h"
#include "Graphics/TerrainRenderer.h"
#include "Graphics/ParticleRenderer.h"

#include "Graphics/GraphicsModule.h"
#include "Graphics/SpriteBatchModule.h"
#elif TIKI_OGL
#include "Graphics/OGLGraphicsModule.h"
#endif

#include <typeinfo.h>

namespace TikiEngine
{
	using namespace TikiEngine::Components;

	TikiInfo DllMain::DllInfo = TikiInfo();
	
	Engine* DllMain::Engine = 0;

	GraphicsModule* DllMain::ModuleGraphics = 0;
	SpriteBatchModule* DllMain::ModuleSpriteBatch = 0;

#if TIKI_DX10
	ID3D10Device* DllMain::Device = 0;
	ID3D10Device* DllMain::Context = 0;
#elif TIKI_DX11
	ID3D11Device* DllMain::Device = 0;
	ID3D11DeviceContext* DllMain::Context = 0;
#elif TIKI_OGL
	HDC DllMain::Device = 0;
	HGLRC DllMain::Context = 0;
	//OGLDllInfo DllMain::Info;
#endif

	void DllMain::InitDll(TikiEngine::Engine* engine)
	{
		DllMain::Engine = engine;
		DllMain::ModuleGraphics = TIKI_NEW GraphicsModule(engine);
		DllMain::ModuleGraphics->AddRef(),
		DllMain::ModuleSpriteBatch = TIKI_NEW SpriteBatchModule(engine);
		DllMain::ModuleSpriteBatch->AddRef(),

		DllInfo.FuncTikiModule = CreateModule;
		DllInfo.FuncTikiResource = CreateResource;
		DllInfo.FuncTikiComponent = CreateComponent;
		DllInfo.FuncTikiResourceExt = GetResourceExt;
		DllInfo.FuncTikiResourcePath = GetResourcePath;
		DllInfo.FuncDispose = DisposeDll;

		DllInfo.Modules.Add(typeid(IGraphics).hash_code());
		DllInfo.Modules.Add(typeid(ISpriteBatch).hash_code());

		DllInfo.Resources.Add(typeid(IFont).hash_code());
		DllInfo.Resources.Add(typeid(IShader).hash_code());
		DllInfo.Resources.Add(typeid(ITexture).hash_code());

#if TIKI_DX10 || TIKI_DX11
		DllInfo.Resources.Add(typeid(IRenderTarget).hash_code());
		DllInfo.Resources.Add(typeid(IModel).hash_code());
		
		DllInfo.Components.Add(typeid(IMeshRenderer).hash_code());
		DllInfo.Components.Add(typeid(ITerrainRenderer).hash_code());
		DllInfo.Components.Add(typeid(IParticleRenderer).hash_code());
#endif
	}

	void DllMain::DisposeDll()
	{
		SafeRelease(&DllMain::ModuleGraphics);
		SafeRelease(&DllMain::ModuleSpriteBatch);
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
		if (hash == typeid(IShader).hash_code())
		{
			return TIKI_NEW Shader(DllMain::Engine);
		}
		else if (hash == typeid(ITexture).hash_code())
		{
			return TIKI_NEW Texture(DllMain::Engine);
		}
		else if (hash == typeid(IFont).hash_code())
		{
			return TIKI_NEW Font(DllMain::Engine);
		}
#if TIKI_DX10 || TIKI_DX11
		else if (hash == typeid(IRenderTarget).hash_code())
		{
			return TIKI_NEW RenderTarget(DllMain::Engine);
		}
		else if(hash == typeid(IModel).hash_code())
		{
			return TIKI_NEW Model(DllMain::Engine);
		}
#endif

		return 0;
	}

	wcstring DllMain::GetResourcePath(PInt hash)
	{
		if (hash == typeid(IShader).hash_code())
		{
#if TIKI_DX10 || TIKI_DX11
			return L"effects";
#elif TIKI_OGL
			return L"effectsgl";
#endif
		}
		else if (hash == typeid(IFont).hash_code())
		{
			return L"font";
		}
		else if (hash == typeid(ITexture).hash_code())
		{
			return L"textures";
		}
		else if (hash == typeid(IRenderTarget).hash_code())
		{
			return L"textures";
		}
#if TIKI_DX10 || TIKI_DX11
		else if(hash == typeid(IModel).hash_code())
		{
			return L"models";
		}
#endif

		return 0;
	}

	wcstring DllMain::GetResourceExt(PInt hash)
	{
		if (hash == typeid(IShader).hash_code())
		{
#if TIKI_DX10 || TIKI_DX11
			return L"fx";
#elif TIKI_OGL
			return L"glsl";
#endif
		}
		else if (hash == typeid(IFont).hash_code())
		{
			return L"ttf";
		}
		else if (hash == typeid(ITexture).hash_code())
		{
			return L"dds";
		}
		else if (hash == typeid(IRenderTarget).hash_code())
		{
			return L"dds";
		}
#if TIKI_DX10 || TIKI_DX11
		else if(hash == typeid(IModel).hash_code())
		{
			return L"tiki";
		}
#endif

		return 0;
	}

	Component* DllMain::CreateComponent(PInt hash, GameObject* gameObject)
	{
#if TIKI_DX10 || TIKI_DX11
		if (hash == typeid(IMeshRenderer).hash_code())
		{
			return TIKI_NEW MeshRenderer(DllMain::Engine, gameObject);
		}
		else if (hash == typeid(ITerrainRenderer).hash_code())
		{
			return TIKI_NEW TerrainRenderer(DllMain::Engine, gameObject);
		}
		else if (hash == typeid(IParticleRenderer).hash_code())
		{
			return TIKI_NEW ParticleRenderer(DllMain::Engine, gameObject);
		}
#endif

		return 0;
	}
}

extern "C" __declspec(dllexport) TikiInfo* GetTikiInfo(Engine* engine)
{
	TikiEngine::DllMain::InitDll(engine);

	return &TikiEngine::DllMain::DllInfo;
}