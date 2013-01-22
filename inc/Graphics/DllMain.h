#pragma once

#include "Core/TikiInfo.h"
#include "Core/Dictionary.h"

#ifdef TIKI_DX10
#include "D3D10_1.h"
#include "D3D10.h"
#include "D3DX10.h"

#define TIKI_VERTEX_BUFFER	D3D10_BIND_VERTEX_BUFFER
#define TIKI_INDEX_BUFFER	D3D10_BIND_INDEX_BUFFER

typedef ID3D10Buffer TDX_Buffer;

typedef ID3D10Texture2D TDX_Texture2D;
typedef D3D10_TEXTURE2D_DESC TDX_Texture2D_Desc;

typedef ID3D10RenderTargetView TDX_RenderTargetView;
typedef D3D10_RENDER_TARGET_VIEW_DESC TDX_RenderTargetView_Desc;

typedef ID3D10ShaderResourceView TDX_ShaderResourceView;
typedef D3D10_SHADER_RESOURCE_VIEW_DESC TDX_ShaderResourceView_Desc;

typedef ID3D10Resource TDX_Resource;

typedef ID3D10InputLayout TDX_InputLayout;
typedef D3D10_INPUT_ELEMENT_DESC TDX_Input_Element_desc;
#else
#include "D3D11.h"
#include "D3DX11.h"

#define TIKI_VERTEX_BUFFER	D3D11_BIND_VERTEX_BUFFER
#define TIKI_INDEX_BUFFER	D3D11_BIND_INDEX_BUFFER

typedef ID3D11Buffer TDX_Buffer;

typedef ID3D11Texture2D TDX_Texture2D;
typedef D3D11_TEXTURE2D_DESC TDX_Texture2D_Desc;

typedef ID3D11RenderTargetView TDX_RenderTargetView;
typedef D3D11_RENDER_TARGET_VIEW_DESC TDX_RenderTargetView_Desc;

typedef ID3D11ShaderResourceView TDX_ShaderResourceView;
typedef D3D11_SHADER_RESOURCE_VIEW_DESC TDX_ShaderResourceView_Desc;

typedef ID3D11Resource TDX_Resource;

typedef ID3D11InputLayout TDX_InputLayout;
typedef D3D11_INPUT_ELEMENT_DESC TDX_Input_Element_desc;
#endif

using TikiEngine::Engine;
using TikiEngine::TikiInfo;

namespace TikiEngine
{
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

		static GraphicsModule* ModuleGraphics;
		static SpriteBatchModule* ModuleSpriteBatch;

#if TIKI_DX10
		static ID3D10Device* Device;
		static ID3D10Device* Context;
#else
		static ID3D11Device* Device;
		static ID3D11DeviceContext* Context;
#endif

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