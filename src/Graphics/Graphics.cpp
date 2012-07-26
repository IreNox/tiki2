
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include "Core\Engine.h"
#include "Graphics\Graphics.h"

#include "Core/Console.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		Graphics::Graphics(Engine* engine)
			: IGraphics(engine), hWnd(0), inited(false), indexBuffer(0), vertexBuffers(), rasterState(0), device(0),
			deviceContext(0), depthStencilState(0), depthStencilView(0), renderTargetView(0)
		{
			clearColor[0] = 0.1;
			clearColor[1] = 0.4;
			clearColor[2] = 0.8;
			clearColor[3] = 1.0;
		}

		Graphics::~Graphics()
		{
			if(swapChain)
			{
				swapChain->SetFullscreenState(false, NULL);
			}

			if (rasterState)
			{
				rasterState->Release();
				rasterState = 0;
			}

			if(depthStencilView)
			{
				depthStencilView->Release();
				depthStencilView = 0;
			}

			if(depthStencilState)
			{
				depthStencilState->Release();
				depthStencilState = 0;
			}

			if(depthStencilBuffer)
			{
				depthStencilBuffer->Release();
				depthStencilBuffer = 0;
			}

			if(renderTargetView)
			{
				renderTargetView->Release();
				renderTargetView = 0;
			}

			if(deviceContext)
			{
				deviceContext->Release();
				deviceContext = 0;
			}

			if(device)
			{
				device->Release();
				device = 0;
			}

			if(swapChain)
			{
				swapChain->Release();
				swapChain = 0;
			}

			if (indexBuffer != 0)
			{
				delete(indexBuffer);
				indexBuffer = 0;
			}

			auto values = vertexBuffers.GetValues();
			for (int i = 0; i < values.Count(); i++)
			{
				delete(values[i]);
			}

			inited = false;
		}
#pragma endregion

		#pragma region Init
		bool Graphics::Initialize(EngineDescription& desc)
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

			viewPort = D3D11_VIEWPORT();
			ZeroMemory(&viewPort, sizeof(viewPort));

			viewPort.Width = (float)swapDesc.BufferDesc.Width;
			viewPort.Height = (float)swapDesc.BufferDesc.Height;
			viewPort.MinDepth = 0.0f;
			viewPort.MaxDepth = 1.0f;
			viewPort.TopLeftX = 0;
			viewPort.TopLeftY = 0;

			deviceContext->RSSetViewports(1, &viewPort);

			this->indexBuffer = new IndexBuffer(this->engine);

			inited = true;
			return true;
		}
		#pragma endregion

		#pragma region Member
		ID3D11Device* Graphics::GetDevice()
		{
			return this->device;
		}

		ID3D11DeviceContext* Graphics::GetDeviceContext()
		{
			return this->deviceContext;
		}

		D3D11_VIEWPORT* Graphics::GetViewPort()
		{
			return &viewPort;
		}

		IndexBuffer* Graphics::GetIndexBuffer()
		{
			return indexBuffer;
		}

		VertexBuffer* Graphics::GetVertexBuffer(VertexDeclaration* decl)
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
		void Graphics::Begin()
		{
			deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
			deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , 1.0f, 0);
		}

		void Graphics::Draw()
		{

		}

		void Graphics::End()
		{
			swapChain->Present(0, 0);
		}
		#pragma endregion

		#pragma region Member - CreateBuffer
		//ID3D11Buffer* Graphics::CreateVertexBuffer(const void* data, UINT size)
		//{
		//	D3D11_BUFFER_DESC desc;
		//	desc.Usage = D3D11_USAGE_DEFAULT;
		//	desc.ByteWidth = size;
		//	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		//	desc.CPUAccessFlags = 0;
		//	desc.MiscFlags = 0;
		//	desc.StructureByteStride = 0;

		//	D3D11_SUBRESOURCE_DATA initData;
		//	initData.pSysMem = data;
		//   
		//	ID3D11Buffer* buffer;

		//	HRESULT r = device->CreateBuffer(
		//		&desc,
		//		&initData,
		//		&buffer
		//	);
		//   
		//	if(FAILED(r)) 
		//	{
		//		return NULL;
		//	}

		//	return buffer;
		//}
		#pragma endregion

		#pragma region Member - CompileShader
		//ID3D11PixelShader* Graphics::CompileShaderPS(const char* code)
		//{
		//	ID3D10Blob* blobPS = NULL;
		//	ID3D10Blob* blobError = NULL;

		//	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
		//#ifdef _DEBUG
		//	dwShaderFlags |= D3D10_SHADER_DEBUG;
		//#endif

		//	HRESULT r = D3DCompile(
		//		code,
		//		lstrlenA(code) + 1,
		//		"PS",
		//		NULL,
		//		NULL,
		//		"PS",
		//		"ps_5_0",
		//		dwShaderFlags,
		//		0,
		//		&blobPS,
		//		&blobError
		//	);

		//	if (FAILED(r))
		//	{
		//		if(blobError != NULL)
		//		{
		//			blobError->Release();
		//		}

		//		return NULL;
		//	}

		//	ID3D11PixelShader* shader;

		//	r = device->CreatePixelShader(
		//		blobPS->GetBufferPointer(),
		//		blobPS->GetBufferSize(),
		//		NULL,
		//		&shader
		//	);

		//	blobPS->Release();

		//	if (FAILED(r))
		//	{
		//		return NULL;
		//	}

		//	return shader;
		//}

		//HRESULT Graphics::CompileShaderVS(const char* code, const D3D11_INPUT_ELEMENT_DESC* inputElements, UINT elementsCount, ID3D11VertexShader** vsShader, ID3D11InputLayout** inputLayout)
		//{
		//	ID3D10Blob* blobVS = NULL;
		//	ID3D10Blob* blobError = NULL;

		//	DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
		//#ifdef _DEBUG
		//	dwShaderFlags |= D3D10_SHADER_DEBUG;
		//#endif

		//	HRESULT r = D3DCompile(
		//		code,
		//		lstrlenA(code) + 1,
		//		"VS",
		//		NULL,
		//		NULL,
		//		"VS",
		//		"vs_5_0",
		//		dwShaderFlags,
		//		0,
		//		&blobVS,
		//		&blobError
		//	);
		//   
		//	if (FAILED(r))
		//	{
		//		if(blobError != NULL)
		//		{
		//			//OutputDebugStringA( (CHAR*)blobError->GetBufferPointer() );
		//			blobError->Release();
		//		}

		//		return r;
		//	}

		//	r = device->CreateVertexShader(
		//		blobVS->GetBufferPointer(),
		//		blobVS->GetBufferSize(),
		//		NULL,
		//		vsShader
		//	);

		//	if (FAILED(r))
		//	{
		//		return r;
		//	}

		//	r = device->CreateInputLayout(
		//		inputElements,
		//		elementsCount,
		//		blobVS->GetBufferPointer(),
		//		blobVS->GetBufferSize(),
		//		inputLayout
		//	);

		//	blobVS->Release();

		//	if (FAILED(r))
		//	{
		//		return r;
		//	}

		//	return r;
		//}
		#pragma endregion
	}
}