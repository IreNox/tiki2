#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include "Core/Engine.h"
#include "Core/Console.h"

#include "Graphics/GraphicsModule.h"
#include "Graphics/DllMain.h"

#include "Core/DrawArgs.h"
#include "Core/Camera.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		GraphicsModule::GraphicsModule(Engine* engine)
			: IGraphics(engine), hWnd(0), inited(false), indexBuffer(0), vertexBuffers(), rasterState(0), device(0),
			deviceContext(0), depthStencilState(0), depthStencilView(0), renderTargetView(0), renderTarget(0)
		{
			clearColor = Color::TikiBlue;
		}

		GraphicsModule::~GraphicsModule()
		{
		}

		void GraphicsModule::Dispose()
		{
			if(swapChain)
			{
				swapChain->SetFullscreenState(false, NULL);
			}

			SafeRelease(&renderTarget);
			SafeRelease(&rasterState);
			SafeRelease(&depthStencilView);
			SafeRelease(&depthStencilState);
			SafeRelease(&depthStencilBuffer);
			SafeRelease(&renderTargetView);
			SafeRelease(&deviceContext);
			SafeRelease(&device);
			SafeRelease(&swapChain);
			SafeRelease(&indexBuffer);

			auto values = vertexBuffers.GetValues();
			for (int i = 0; i < values.Count(); i++)
			{
				delete(values[i]);
			}

			inited = false;
		}
		#pragma endregion

		#pragma region Init
		bool GraphicsModule::Initialize(EngineDescription& desc)
		{
			if (inited) return false;

			hWnd = desc.Window.hWnd;

			RECT rect;
			GetClientRect(hWnd, &rect);

			DXGI_SWAP_CHAIN_DESC swapDesc;
			ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

			swapDesc.BufferCount = 2;
			swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			swapDesc.BufferDesc.Height = rect.bottom;
			swapDesc.BufferDesc.Width = rect.right;
			swapDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapDesc.OutputWindow = hWnd;
			swapDesc.SampleDesc.Count = 1;
			swapDesc.SampleDesc.Quality = 0;
			swapDesc.Windowed = true;
			swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

			D3D_FEATURE_LEVEL level;
			D3D_FEATURE_LEVEL levels = D3D_FEATURE_LEVEL_11_0;

			HRESULT r = D3D11CreateDeviceAndSwapChain(
				NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				0, // DEBUG FLAG
				&levels,
				1,
				D3D11_SDK_VERSION,
				&swapDesc,
				&swapChain,
				&device,
				&level,
				&deviceContext
				);

			if (FAILED(r)) { return false; }

			ID3D11Texture2D* backBufferPtr;
			r = swapChain->GetBuffer(
				0,
				__uuidof(ID3D11Texture2D),
				(LPVOID*)&backBufferPtr
			);

			if (FAILED(r)) { return false; }

			r = device->CreateRenderTargetView(backBufferPtr, NULL, &renderTargetView);
			backBufferPtr->Release();

			if (FAILED(r)) { return false; }

			D3D11_TEXTURE2D_DESC depthDesc;
			ZeroMemory(&depthDesc, sizeof(depthDesc));

			depthDesc.Width = swapDesc.BufferDesc.Width;
			depthDesc.Height = swapDesc.BufferDesc.Height;
			depthDesc.MipLevels = 1;
			depthDesc.ArraySize = 1;
			depthDesc.Format =  DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthDesc.SampleDesc.Count = 1;
			depthDesc.SampleDesc.Quality = 0;
			depthDesc.Usage = D3D11_USAGE_DEFAULT;
			depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthDesc.CPUAccessFlags = 0;
			depthDesc.MiscFlags = 0;

			r = device->CreateTexture2D(
				&depthDesc,
				NULL,
				&depthStencilBuffer
			);

			if (FAILED(r)) { return false; }

			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

			depthStencilDesc.DepthEnable = true;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

			depthStencilDesc.StencilEnable = true;
			depthStencilDesc.StencilReadMask = 0xFF;
			depthStencilDesc.StencilWriteMask = 0xFF;

			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			r = device->CreateDepthStencilState(
				&depthStencilDesc,
				&depthStencilState
			);
			deviceContext->OMSetDepthStencilState(depthStencilState, 1);

			if (FAILED(r)) { return false; }

			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
			ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

			depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			depthStencilViewDesc.Texture2D.MipSlice = 0;

			r = device->CreateDepthStencilView(
				depthStencilBuffer,
				&depthStencilViewDesc,
				&depthStencilView
			);

			if (FAILED(r)) { return false; }

			deviceContext->OMSetRenderTargets(
				1,
				&renderTargetView,
				depthStencilView
			);

			D3D11_RASTERIZER_DESC rasterDesc;

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_NONE;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			r = device->CreateRasterizerState(
				&rasterDesc,
				&rasterState
			);

			if(FAILED(r))
			{
				Console::WriteError("Can't create RasterizerState", r);
			}

			deviceContext->RSSetState(rasterState);

			D3D11_VIEWPORT viewPort = D3D11_VIEWPORT();
			ZeroMemory(&viewPort, sizeof(viewPort));

			viewPort.Width = (float)swapDesc.BufferDesc.Width;
			viewPort.Height = (float)swapDesc.BufferDesc.Height;
			viewPort.MinDepth = 0.0f;
			viewPort.MaxDepth = 1.0f;
			viewPort.TopLeftX = 0;
			viewPort.TopLeftY = 0;
			
			this->viewPort = ViewPort(
				viewPort.TopLeftX,
				viewPort.TopLeftY,
				viewPort.Width,
				viewPort.Height,
				viewPort.MinDepth,
				viewPort.MaxDepth
			);
			desc.Graphics.ViewPort = this->viewPort;

			deviceContext->RSSetViewports(1, &viewPort);

			DllMain::Device = device;
			DllMain::Context = deviceContext;

			this->indexBuffer = new IndexBuffer(engine);
			this->matrixBuffer = new ConstantBuffer<Matrices>(engine);
			this->renderTarget = new RenderTarget(engine, renderTargetView);

			inited = true;
			return true;
		}
		#pragma endregion

		#pragma region Member - Get
		void* GraphicsModule::GetDevice()
		{
			return (void*)this->device;
		}

		void* GraphicsModule::GetDeviceContext()
		{
			return (void*)this->deviceContext;
		}

		ViewPort* GraphicsModule::GetViewPort()
		{
			return &viewPort;
		}

		IRenderTarget* GraphicsModule::GetBackBufferRenderTarget()
		{
			return renderTarget;
		}
		#pragma endregion

		#pragma region Member - Get - Buffer
		IndexBuffer* GraphicsModule::GetIndexBuffer()
		{
			return indexBuffer;
		}

		ConstantBuffer<Matrices>* GraphicsModule::GetMatrixBuffer()
		{
			return matrixBuffer;
		}

		VertexBuffer* GraphicsModule::GetVertexBuffer(VertexDeclaration* decl)
		{
			ULONG hash = decl->GetDeclarationHash();

			if (!vertexBuffers.ContainsKey(hash))
			{
				vertexBuffers.Add(
					hash, 
					new VertexBuffer(engine, decl)
					);
			}

			return vertexBuffers.Get(hash);		
		}
		#pragma endregion

		#pragma region Member - Draw
		void GraphicsModule::Begin(const DrawArgs& args)
		{
			deviceContext->ClearRenderTargetView(renderTargetView, clearColor.arr);
			deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , 1.0f, 0);

			if (args.Context.CurrentCamera)
			{
				Matrices* matrices = matrixBuffer->Map();
				*matrices = *args.Context.CurrentCamera->GetMatrices();
				matrixBuffer->Unmap();
			}
		}

		void GraphicsModule::End()
		{
			swapChain->Present(0, 0);
		}
		#pragma endregion
	}
}