#pragma once

#include "Core\IGraphics.h"

#include <D3D11.h>
#include <D3DX11.h>

#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBuffer.h"

#include "Core/Dictionary.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Buffer;

		class Graphics : public IGraphics
		{
		public:
			Graphics(Engine* engine);
			~Graphics();

			bool Initialize(const EngineDescription* desc);

			void Begin();

			void Draw();

			void End();

			void Dispose();

			void Clear(float* color);
			void Present();

			//ID3D11PixelShader* CompileShaderPS(const char* code);
			//HRESULT CompileShaderVS(const char* code, const D3D11_INPUT_ELEMENT_DESC* inputElements, UINT elementsCount, ID3D11VertexShader** vsShader, ID3D11InputLayout** inputLayout);

			//ID3D11Buffer* CreateVertexBuffer(const void* data, UINT size);
			//ID3D11InputLayout* CreateInputLayout();

			ID3D11Device* GetDevice();
			ID3D11DeviceContext* GetDeviceContext();

			D3D11_VIEWPORT* GetViewPort();

			IndexBuffer* GetIndexBuffer();
			VertexBuffer* GetVertexBuffer(VertexDeclaration* decl);

		private:
			HWND hWnd;
			Engine* engine;

			bool inited;

			ID3D11Device* device;
			ID3D11DeviceContext* deviceContext;

			IDXGISwapChain* swapChain;
			ID3D11RenderTargetView* renderTargetView; 

			ID3D11Texture2D* depthStencilBuffer;
			ID3D11DepthStencilView* depthStencilView;
			ID3D11DepthStencilState* depthStencilState;

			D3D11_VIEWPORT viewPort; 
			ID3D11RasterizerState* rasterState;

			IndexBuffer* indexBuffer;
			Dictionary<ULONG, VertexBuffer*> vertexBuffers;
		};
	}
}