#pragma once

#include "Core/TypeGlobals.h"
#include "Core/Dictionary.h"

#include "Core/CBMatrices.h"
#include "Graphics/CBLights.h"
#include "Graphics/CBObjectData.h"

#include "Core/IGraphics.h"

#include "Graphics/Quad.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/ConstantBuffer.h"

#if _DEBUG
#include "Graphics/DebugLineRenderer.h"
#endif

#if TIKI_DX10
#include "D3D10.h"
#include "D3DX10.h"
#else
#include "D3D11.h"
#include "D3DX11.h"
#endif

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Graphics;

		class GraphicsModule : public IGraphics
		{
		public:

#if _DEBUG
			DebugLineRenderer* debugLineRenderer;
#endif

			GraphicsModule(Engine* engine);
			~GraphicsModule();

			bool Initialize(EngineDescription& desc);

			void Begin(DrawArgs& args);
			void End();

#if _DEBUG
			void DrawLine(const Vector3& start, const Vector3& end, const Color& color);
			void DrawLine(List<Vector3>* points, const Color& color, bool lastToFirst = false);
#endif
			
			void Dispose();

			void* GetDevice();
			void* GetDeviceContext();

			ViewPort* GetViewPort();
			IRenderTarget* GetDepthTarget() { return rtDepth; }
			IRenderTarget* GetLightTarget() { return rtLight; }
			IRenderTarget* GetNormalTarget() { return rtNormal; }
			IRenderTarget* GetScreenTarget() { return rtScreen[rtScreenIndex]; }
			IRenderTarget* GetUnusedScreenTarget() { return rtScreen[!rtScreenIndex]; }
			IRenderTarget* GetInterfaceTarget() { return rtInterface; }

			void Reset();

			void MakeScreenshot(wcstring fileName);

			ConstantBuffer<CBLights>* GetCBufferLight();
			ConstantBuffer<CBMatrices>* GetCBufferCamera();
			ConstantBuffer<CBObjectData>* GetCBufferObject();

			void AddPostProcess(PostProcess* postProcess);
			void RemovePostProcess(PostProcess* postProcess);

			void AddScreenSizeRenderTarget(RenderTarget* target);
			void RemoveScreenSizeRenderTarget(RenderTarget* target);

			void AddDefaultProcessTarget(cstring varName, IRenderTarget* target);
			void SwitchScreenTarget(IRenderTarget** inputTarget, IRenderTarget** outputTarget);

			void SetRenderTarget(UInt32 slot, TDX_RenderTargetView* target);
			void SetFirstAndOnlyRenderTargets(TDX_RenderTargetView* target);

			void SetCulling(bool value);
			void SetStateAlphaBlend(BlendStateModes value);
			void SetStateDepthEnabled(bool value);

			IConstantBuffer* CreateConstantBuffer(UInt32 size);

			bool GetReady();

		private:

			bool inited;
			DrawArgs& currentArgs;

			Color clearColor;
			ViewPort viewPort; 

			IDXGIFactory* factory;
			IDXGIAdapter* adapter;
			IDXGISwapChain* swapChain;

#if TIKI_DX10
			ID3D10Device* device;
			ID3D10Device* deviceContext;
			ID3D10RenderTargetView* renderTargetView;

			ID3D10Texture2D* depthStencilBuffer;
			ID3D10DepthStencilView* depthStencilView;
			ID3D10DepthStencilState* depthStencilState;
			ID3D10DepthStencilState* depthStencilStateDisable;

			ID3D10BlendState* blendStateInterface;
			ID3D10BlendState* blendStateParticle;
			ID3D10RasterizerState* rasterStateBackfaces;

			List<ID3D10RenderTargetView*> renderTargets;
#else
			ID3D11Device* device;
			ID3D11DeviceContext* deviceContext;
			ID3D11RenderTargetView* renderTargetView;

			ID3D11Texture2D* depthStencilBuffer;
			ID3D11DepthStencilView* depthStencilView;
			ID3D11DepthStencilState* depthStencilState;
			ID3D11DepthStencilState* depthStencilStateDisable;

			ID3D11BlendState* blendStateInterface;
            ID3D11BlendState* blendStateParticle;
			ID3D11RasterizerState* rasterStateBackfaces;

			List<ID3D11RenderTargetView*> renderTargets;
#endif

			ConstantBuffer<CBLights>* cbufferLights;
			ConstantBuffer<CBMatrices>* cbufferCamera;
			ConstantBuffer<CBObjectData>* cbufferObject;

			RenderTarget* rtBackBuffer;
			RenderTarget* rtLight;
			RenderTarget* rtDepth;
			RenderTarget* rtNormal;
			RenderTarget* rtInterface;
			RenderTarget* rtScreen[2];
			bool rtScreenIndex;

			List<RenderTarget*> screenSizeRenderTargets;

			PostProcess* defaultPostProcess;
			PostProcessPass* defaultPostProcessPass;
			List<PostProcess*> postProcesses;
			Dictionary<PostProcessPass*, Quad*> postProcessPassQuads;

			bool initSelectAdapter(EngineDescription& desc);
			bool initDirectX(EngineDescription& desc);
			bool initDirectXBackBuffer(EngineDescription& desc);
			bool initDirectXDepthStencil(EngineDescription& desc);
			bool initDirectXViewPort(EngineDescription& desc);
			bool initEngine(EngineDescription& desc);

			void drawPostProcess(PostProcess* postProcess);

			void setLightChanged(const DrawArgs& args);

		};
	}
}
