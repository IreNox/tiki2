#pragma once

#include "Core/TypeGlobals.h"
#include "Core/Dictionary.h"

#include "Core/CBMatrices.h"
#include "Graphics/CBLights.h"
#include "Graphics/CBObjectData.h"

#include "Core/IGraphics.h"

#include "Graphics/Quad.h"

#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/ConstantBuffer.h"

#include "Graphics/RenderTarget.h"

#if _DEBUG
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

			void Clear(float* color);

			void* GetDevice();
			void* GetDeviceContext();

			ViewPort* GetViewPort();
			IRenderTarget* GetScreenTarget();
			IRenderTarget* GetNormalTarget();
			IRenderTarget* GetDepthTarget();

			void Reset();

			void MakeScreenshot(wcstring fileName);

			ConstantBuffer<CBLights>* GetCBufferLight();
			ConstantBuffer<CBMatrices>* GetCBufferCamera();
			ConstantBuffer<CBObjectData>* GetCBufferObject();

			IndexBuffer* GetIndexBuffer();
			VertexBuffer* GetVertexBuffer(VertexDeclaration* decl, bool dynamic);

			void AddPostProcess(PostProcess* postProcess);
			void AddDefaultProcessTarget(cstring varName, IRenderTarget* target);
			void AddScreenSizeRenderTarget(RenderTarget* target);

			void RemovePostProcess(PostProcess* postProcess);
			void RemoveScreenSizeRenderTarget(RenderTarget* target);

			void SetRenderTarget(UInt32 slot, ID3D11RenderTargetView* target);
			void SetFirstAndOnlyRenderTargets(ID3D11RenderTargetView* target);

			void SetStateAlphaBlend(bool value);
			void SetStateDepthEnabled(bool value);

			bool GetReady();

		private:

			bool inited;
			DrawArgs currentArgs;

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
			ID3D11BlendState* blendStateAlphaBlendDisabled;
			ID3D11RasterizerState* rasterStateBackfaces;

			Color clearColor;
			ConstantBuffer<CBLights>* cbufferLights;
			ConstantBuffer<CBMatrices>* cbufferCamera;
			ConstantBuffer<CBObjectData>* cbufferObject;

			IndexBuffer* indexBuffer;
			Dictionary<ULONG, VertexBuffer*> vertexBuffers;

			List<ID3D11RenderTargetView*> renderTargets;

			RenderTarget* rtDepth;
			RenderTarget* rtNormal;
			RenderTarget* rtScreen;
			RenderTarget* rtBackBuffer;
			List<RenderTarget*> screenSizeRenderTargets;

			PostProcess* defaultPostProcess;
			List<PostProcess*> postProcesses;
			Dictionary<PostProcessPass*, Quad*> postProcessPassQuads;

#if _DEBUG
			DebugLineRenderer* lineRenderer;
#endif

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
