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
#include "Graphics/DebugConsole.h"
#include "Graphics/DebugLineRenderer.h"
#endif

#include <D3D11.h>
#include <D3DX11.h>

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Graphics;

		class GraphicsModule : public IGraphics
		{
		public:

#if _DEBUG
			DebugConsole* debugConsole;
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

			void DrawConsole(const DrawArgs& args);
#endif
			
			void Dispose();

			void Clear(float* color);

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

			void SetRenderTarget(UInt32 slot, ID3D11RenderTargetView* target);
			void SetFirstAndOnlyRenderTargets(ID3D11RenderTargetView* target);

			void SetStateAlphaBlend(bool value);
			void SetStateDepthEnabled(bool value);

			IConstantBuffer* CreateConstantBuffer(UInt32 size);

			bool GetReady();

		private:

			bool inited;
			DrawArgs& currentArgs;

			IDXGIFactory* factory;
			IDXGIAdapter* adapter;

			ID3D11Device* device;
			ID3D11DeviceContext* deviceContext;

			IDXGISwapChain* swapChain;
			ID3D11RenderTargetView* renderTargetView;

			ID3D11Texture2D* depthStencilBuffer;
			ID3D11DepthStencilView* depthStencilView;
			ID3D11DepthStencilState* depthStencilState;
			ID3D11DepthStencilState* depthStencilStateDisable;

			ViewPort viewPort; 
			ID3D11BlendState* blendStateAlphaBlend;
			ID3D11RasterizerState* rasterStateBackfaces;

			Color clearColor;
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
			List<ID3D11RenderTargetView*> renderTargets;

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
