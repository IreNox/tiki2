#pragma once

#include "Core/TypeGlobals.h"
#include "Core/Dictionary.h"

#include "Core/Matrices.h"
#include "Graphics/Lights.h"

#include "Core/IGraphics.h"

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
		using namespace TikiEngine::Buffer;
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
			IRenderTarget* GetBackBufferRenderTarget();

			ConstantBuffer<Matrices>* GetMatrixBuffer();

			IndexBuffer* GetIndexBuffer();
			VertexBuffer* GetVertexBuffer(VertexDeclaration* decl);

			void SetLightChanged(List<Light*>* lights);

			bool GetReady();

		private:

			bool inited;

			ID3D11Device* device;
			ID3D11DeviceContext* deviceContext;

			IDXGISwapChain* swapChain;
			ID3D11RenderTargetView* renderTargetView;
			RenderTarget* renderTarget;

			ID3D11Texture2D* depthStencilBuffer;
			ID3D11DepthStencilView* depthStencilView;
			ID3D11DepthStencilState* depthStencilState;

			ViewPort viewPort; 
			ID3D11RasterizerState* rasterState;

			Color clearColor;
			ConstantBuffer<Lights>* lightBuffer;
			ConstantBuffer<Matrices>* matrixBuffer;


			IndexBuffer* indexBuffer;
			Dictionary<ULONG, VertexBuffer*> vertexBuffers;
		};
	}
}