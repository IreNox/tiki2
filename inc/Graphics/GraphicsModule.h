#pragma once

#include "Core/TypeGlobals.h"
#include "Core/Matrices.h"

#include "Core/IGraphics.h"
#include "Core/Dictionary.h"

#include <D3D11.h>
#include <D3DX11.h>

#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/ConstantBuffer.h"

#include "Graphics/RenderTarget.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Buffer;

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

			bool GetReady();

		private:
			HWND hWnd;

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

			float clearColor[4];
			ConstantBuffer<Matrices>* matrixBuffer;

			IndexBuffer* indexBuffer;
			Dictionary<ULONG, VertexBuffer*> vertexBuffers;
		};
	}
}