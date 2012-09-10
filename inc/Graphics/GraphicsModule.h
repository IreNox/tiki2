#pragma once

#include "Core/TypeGlobals.h"
#include "Core/Dictionary.h"

#include "Core/Matrices.h"
#include "Graphics/Lights.h"

#include "Core/IGraphics.h"

#include "Graphics/Quad.h"

#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/ConstantBuffer.h"

#include "Graphics/RenderTarget.h"

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

			void Begin(const DrawArgs& args);
			void End();

			void Dispose();

			void Clear(float* color);
			void Present();

			void* GetDevice();
			void* GetDeviceContext();

			ViewPort* GetViewPort();
			IRenderTarget* GetScreenBuffer();

			ConstantBuffer<Lights>* GetLightBuffer();
			ConstantBuffer<Matrices>* GetMatrixBuffer();

			IndexBuffer* GetIndexBuffer();
			VertexBuffer* GetVertexBuffer(VertexDeclaration* decl, bool dynamic);

			void AddPostProcess(PostProcess* postProcess);
			void AddDefaultProcessTarget(string varName, IRenderTarget* target);
			void RemovePostProcess(PostProcess* postProcess);

			void AddScreenSizeRenderTarget(RenderTarget* target);
			void RemoveScreenSizeRenderTarget(RenderTarget* target);

			void SetLightChanged(List<Light*>* lights);
			void SetRenderTarget(UInt32 slot, ID3D11RenderTargetView* target);

			bool GetReady();

		private:

			bool inited;
			GameTime currentTime;

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
			ID3D11BlendState* alphaBlendState;
			ID3D11RasterizerState* rasterStateBackfaces;

			Color clearColor;
			ConstantBuffer<Lights>* lightBuffer;
			ConstantBuffer<Matrices>* matrixBuffer;
			
			IndexBuffer* indexBuffer;
			Dictionary<ULONG, VertexBuffer*> vertexBuffers;

			List<ID3D11RenderTargetView*> renderTargets;

			RenderTarget* rtScreen;
			RenderTarget* rtBackBuffer;

			PostProcess* defaultPostProcess;
			List<PostProcess*> postProcesses;
			Dictionary<PostProcessPass*, Quad*> postProcessPassQuads;

			bool initSelectAdapter(EngineDescription& desc);
			bool initDirectX(EngineDescription& desc);
			bool initEngine(EngineDescription& desc);

			void drawPostProcess(PostProcess* postProcess);

		};
	}
}