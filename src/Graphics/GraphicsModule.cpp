#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include "Core/Engine.h"
#include "Core/IContentManager.h"
#include "Core/Console.h"

#include "Graphics/GraphicsModule.h"
#include "Graphics/DllMain.h"

#include "Core/DrawArgs.h"
#include "Core/Camera.h"

#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		GraphicsModule::GraphicsModule(Engine* engine)
			: IGraphics(engine), inited(false), indexBuffer(0), vertexBuffers(), rasterState(0), device(0),
			deviceContext(0), depthStencilState(0), depthStencilView(0), renderTargetView(0), matrixBuffer(0),
			lightBuffer(0), rtScreen(0), rtBackBuffer(0), renderTargets()
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

			SafeRelease(&rtScreen);
			SafeRelease(&rtBackBuffer);
			SafeRelease(&quadPostProcess);
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
			for (UInt32 i = 0; i < values.Count(); i++)
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

			bool ok = true;

			if (ok) ok &= initDirectX(desc);
			if (ok) ok &= initEngine(desc);

			inited = ok;
			return ok;
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

		IRenderTarget* GraphicsModule::GetScreenBuffer()
		{
			return rtScreen;
		}
		#pragma endregion

		#pragma region Member - Get - Buffer
		IndexBuffer* GraphicsModule::GetIndexBuffer()
		{
			return indexBuffer;
		}

		ConstantBuffer<Lights>* GraphicsModule::GetLightBuffer()
		{
			return lightBuffer;
		}

		ConstantBuffer<Matrices>* GraphicsModule::GetMatrixBuffer()
		{
			return matrixBuffer;
		}

		VertexBuffer* GraphicsModule::GetVertexBuffer(VertexDeclaration* decl, bool dynamic)
		{
			ULONG hash = decl->GetDeclarationHash() + dynamic;

			if (!vertexBuffers.ContainsKey(hash))
			{
				vertexBuffers.Add(
					hash,
					new VertexBuffer(engine, decl, dynamic)
				);
			}

			return vertexBuffers.Get(hash);		
		}
		#pragma endregion

		#pragma region Member - Set
		void GraphicsModule::SetLightChanged(List<Light*>* lights)
		{
			Lights* buf = lightBuffer->Map();
			*buf = Lights();

			buf->Count = (float)lights->Count();
			if (buf->Count > 32) buf->Count = 32;

			UInt32 i = 0;
			while (i < buf->Count)
			{
				Light* l = lights->Get(i);

				buf->Data[i].Range = l->GetRange();
				buf->Data[i].Color = l->GetColor().ToVector4();
				buf->Data[i].Position = l->GetGameObject()->PRS.Position;
				buf->Data[i].Direction = l->GetGameObject()->PRS.Rotation * Vector3::ForwardRH;

				i++;
			}

			lightBuffer->Unmap();
		}

		void GraphicsModule::SetRenderTarget(UInt32 slot, ID3D11RenderTargetView* target)
		{
			while (slot >= renderTargets.Count())
			{
				renderTargets.Add(0);
			}

			renderTargets[slot] = target;

			ID3D11RenderTargetView** targets = renderTargets.ToArray();

			deviceContext->OMSetRenderTargets(
				renderTargets.Count(),
				targets,
				depthStencilView
			);

			delete[](targets);
		}
		#pragma endregion

		#pragma region Member - Draw
		void GraphicsModule::Begin(const DrawArgs& args)
		{
			rtScreen->Apply(0);
			rtScreen->Clear(clearColor);
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
			quadPostProcess->Draw();

			swapChain->Present(0, 0);
		}
		#pragma endregion

		#pragma region Private Member - Init - DirectX
		bool GraphicsModule::initDirectX(EngineDescription& desc)
		{
			RECT rect;
			GetClientRect(desc.Window.hWnd, &rect);

			DXGI_SWAP_CHAIN_DESC swapDesc;
			ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

			swapDesc.BufferCount = 2;
			swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			swapDesc.BufferDesc.Height = rect.bottom;
			swapDesc.BufferDesc.Width = rect.right;
			swapDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapDesc.OutputWindow = desc.Window.hWnd;
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

			deviceContext->RSSetState(rasterState); // back face culling

			D3D11_VIEWPORT viewPort = D3D11_VIEWPORT();
			ZeroMemory(&viewPort, sizeof(viewPort));

			viewPort.Width = (float)swapDesc.BufferDesc.Width;
			viewPort.Height = (float)swapDesc.BufferDesc.Height;
			viewPort.MinDepth = 0.0f;
			viewPort.MaxDepth = 1.0f;
			viewPort.TopLeftX = 0;
			viewPort.TopLeftY = 0;

			this->viewPort = ViewPort(
				(Int32)viewPort.TopLeftX,
				(Int32)viewPort.TopLeftY,
				(Int32)viewPort.Width,
				(Int32)viewPort.Height,
				viewPort.MinDepth,
				viewPort.MaxDepth
				);
			desc.Graphics.ViewPort = this->viewPort;

			deviceContext->RSSetViewports(1, &viewPort);

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Init - Engine
		bool GraphicsModule::initEngine(EngineDescription& desc)
		{
			DllMain::Device = device;
			DllMain::Context = deviceContext;

			this->indexBuffer = new IndexBuffer(engine);
			this->lightBuffer = new ConstantBuffer<Lights>(engine);
			this->matrixBuffer = new ConstantBuffer<Matrices>(engine);

			this->rtBackBuffer = new RenderTarget(engine, renderTargetView);

			this->rtScreen = new RenderTarget(engine);
			this->rtScreen->Create(rtBackBuffer->GetWidth(), rtBackBuffer->GetHeight());

			IShader* shader = new Shader(engine);
			shader->LoadFromFile(L"Data/Effects/pp_default.fx");
			shader->SetTexture("tex", rtScreen);

			quadPostProcess = new Quad(engine);
			quadPostProcess->SetShader(shader);
			quadPostProcess->SetRenderTarget(rtBackBuffer);

			SafeRelease(&shader);

			return true;
		}
		#pragma endregion
	}
}
