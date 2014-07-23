#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include "Core/Engine.h"
#include "Core/IContentManager.h"

#include "Graphics/DXGraphicsModule.h"
#include "Graphics/SpriteBatchModule.h"
#include "Graphics/DllMain.h"

#include "Core/GameObject.h"

#include "Core/FileStream.h"
using namespace TikiEngine::IO;

#include <ctime>
#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		GraphicsModule::GraphicsModule(Engine* engine)
			: IGraphics(engine), inited(false), rasterStateBackfaces(0), device(0), blendStateParticle(0),  blendStateInterface(0),
			depthStencilState(0), depthStencilView(0), renderTargetView(0), rtBackBuffer(0), renderTargets(), postProcesses(),
			postProcessPassQuads(), defaultPostProcess(0), currentArgs(DrawArgs::Empty), depthStencilStateDisable(0),
			screenSizeRenderTargets(), factory(0), adapter(0), swapChain(0), depthStencilBuffer(0), cbufferLights(0),
			cbufferCamera(0), cbufferObject(0), rtScreenIndex(0), defaultPostProcessPass(0), deviceContext(0)
#if _DEBUG
			, debugLineRenderer(0)
#endif
		{
			clearColor = Color::TikiBlue;

			rtScreen[0] = 0;
			rtScreen[1] = 0;
		}

		GraphicsModule::~GraphicsModule()
		{
		}
		#pragma endregion

		#pragma region Member - Init/Dispose
		bool GraphicsModule::Initialize(EngineDescription& desc)
		{
			if (inited) return false;

			bool ok = true;

			if (ok) ok &= initSelectAdapter(desc);
			if (ok) ok &= initDirectX(desc);
			if (ok) ok &= initEngine(desc);

			inited = ok;
			return ok;
		}

		void GraphicsModule::Dispose()
		{
			if(swapChain)
			{
				swapChain->SetFullscreenState(false, NULL);
			}
			
#if _DEBUG
			SafeRelease(&debugLineRenderer);
#endif

			disposeEngine();

			SafeRelease(&blendStateParticle);
            SafeRelease(&blendStateInterface);

			SafeRelease(&depthStencilState);
			SafeRelease(&depthStencilStateDisable);
			SafeRelease(&rasterStateBackfaces);

			SafeRelease(&depthStencilView);
			SafeRelease(&depthStencilBuffer);
			SafeRelease(&renderTargetView);
#if TIKI_DX11
			SafeRelease(&deviceContext);
#endif
			SafeRelease(&device);
			SafeRelease(&swapChain);

			SafeRelease(&adapter);
			SafeRelease(&factory);

			inited = false;
		}
		#pragma endregion

		#pragma region Member
		void GraphicsModule::MakeScreenshot(wcstring fileName)
		{
			bool TIKI_NEWName = false;
			if (fileName == 0)
			{
				time_t now = time(0);

				tm time;
				localtime_s(&time, &now);

				wstring s = L"Screenshot.dds";
				//s << L"Screenshot-" << (time.tm_year + 1900) << "-" << (time.tm_mon + 1) << "-" << time.tm_mday << "-" << time.tm_hour << "-" << time.tm_min << "-" << time.tm_sec << ".dds";

				wchar_t* fileName2 = TIKI_NEW wchar_t[s.Length() + 1];
				memcpy(fileName2, s.CStr(), sizeof(wchar_t) * (s.Length() + 1));

				fileName = fileName2;
				TIKI_NEWName = true;
			}

			wstring path = engine->HPath.CombineWorkingPath(wstring(L"Screenshots/") + fileName);

			rtBackBuffer->SaveToFile(
				path.CStr()
			);

			//IRenderTarget* oldTarget = defaultPostProcess->GetPasses()->Get(0)->GetOutput()->Get(0);
			//
			//IRenderTarget* target = TIKI_NEW RenderTarget(engine);
			//target->CreateScreenSize(true);
			//defaultPostProcess->GetPasses()->Get(0)->SetOutput(0, target);

			//drawPostProcess(defaultPostProcess);

			//defaultPostProcess->GetPasses()->Get(0)->SetOutput(0, oldTarget);

			//UInt32 len = 0;
			//void* data = 0;
			//target->GetData(PF_A8R8G8B8, &data, &len);

			//FileStream stream(fileName, FileMode::FM_Write);
			//stream.Write(data, 0, len);

			if (TIKI_NEWName)
			{
				SafeDelete(&fileName);
			}
		}
		#pragma endregion

		#pragma region Member - Reset
		void GraphicsModule::Reset()
		{
			EngineDescription& desc = engine->GetEngineDescription();
			
			if (desc.Graphics.Fullscreen)
			{
				RECT rect;
				HWND hDesktop = GetDesktopWindow();
				GetWindowRect(hDesktop, &rect);

				desc.Graphics.Width = rect.right;
				desc.Graphics.Height = rect.bottom;
			}

			DXGI_MODE_DESC modeDesc;
			modeDesc.Format = DXGI_FORMAT_UNKNOWN;
			modeDesc.Width = desc.Graphics.Width;
			modeDesc.Height = desc.Graphics.Height;
			modeDesc.RefreshRate.Denominator = 1;
			modeDesc.RefreshRate.Numerator = 60;
			modeDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
			modeDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

			HRESULT r = swapChain->ResizeTarget(&modeDesc);

			if (FAILED(r))
			{
				engine->HLog.Write("Warning: Can't resize BackTarget.");
				return;
			}

			depthStencilView->Release();
			depthStencilBuffer->Release();

			renderTargets.Clear();
			deviceContext->OMSetRenderTargets(0, 0, 0);
			renderTargetView->Release();

			TDX_Texture2D* backBuffer;
			swapChain->GetBuffer(0, __uuidof(TDX_Texture2D), (void**)&backBuffer);
			while (backBuffer->Release()) {}

			r = swapChain->ResizeBuffers(
				0,
				desc.Graphics.Width,
				desc.Graphics.Height,
				DXGI_FORMAT_UNKNOWN,
				DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
			);

			r = swapChain->SetFullscreenState(desc.Graphics.Fullscreen, NULL);

			if (FAILED(r))
			{
				engine->HLog.Write("Warning: Can't change Fullscreen mode.");
			}

			if (FAILED(r))
			{
				engine->HLog.Write("Warning: Can't resize BackBuffer.");
			}

			if (initDirectXBackBuffer(desc) &&
				initDirectXDepthStencil(desc) &&
				initDirectXViewPort(desc))
			{
				this->rtBackBuffer->Resize(renderTargetView);

				UInt32 i = 0;
				while (i < screenSizeRenderTargets.Count())
				{
					screenSizeRenderTargets[i]->Resize(desc.Graphics.Width, desc.Graphics.Height);
					i++;
				}

				this->ScreenSizeChanged.RaiseEvent(this, ScreenSizeChangedArgs(this, &viewPort));
			}
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
		#pragma endregion

		#pragma region Member - Set
		void GraphicsModule::SetRenderTarget(UInt32 slot, TDX_RenderTargetView* target)
		{
			while (slot >= renderTargets.Count())
			{
				renderTargets.Add(0);
			}

			if (renderTargets[slot] == target) return;
			renderTargets[slot] = target;

			deviceContext->OMSetRenderTargets(
				renderTargets.Count(),
				renderTargets.GetInternalData(),
				depthStencilView
			);
		}

		void GraphicsModule::SetFirstAndOnlyRenderTargets(TDX_RenderTargetView* target)
		{
			renderTargets.Clear();
			this->SetRenderTarget(0, target);
		}

		void GraphicsModule::SetCulling(bool value)
		{

		}

		void GraphicsModule::SetStateAlphaBlend(BlendStateModes value)
		{			
			//static float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

            switch(value)
            {
            case BSM_Interface:
                deviceContext->OMSetBlendState(blendStateInterface, 0, 0xffffffff);
                break;

            case BSM_Particles:
                deviceContext->OMSetBlendState(blendStateParticle, 0, 0xffffffff);
                break;

            case BSM_Disable:
                deviceContext->OMSetBlendState(0, 0, 0xffffffff);
                break;


            }
		}

		void GraphicsModule::SetStateDepthEnabled(bool value)
		{
			if (value)
			{
				deviceContext->OMSetDepthStencilState(depthStencilState, 1);
			}
			else
			{
				deviceContext->OMSetDepthStencilState(depthStencilStateDisable, 1);
			}
		}
		#pragma endregion

		#pragma region Member - Debug
#if _DEBUG
		void GraphicsModule::DrawLine(const Vector3& start, const Vector3& end, const Color& color)
		{
			debugLineRenderer->DrawLine(start, end, color);
		}

		void GraphicsModule::DrawLine(List<Vector3>* points, const Color& color, bool lastToFirst)
		{
			debugLineRenderer->DrawLine(points, color, lastToFirst);
		}
#endif
		#pragma endregion
		
		#pragma region Private Member - Init - SelectAdapter
		bool GraphicsModule::initSelectAdapter(EngineDescription& desc)
		{
			HRESULT r = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
			if(FAILED(r))
			{
				return false;
			}

			r = factory->EnumAdapters(desc.Graphics.AdapterIndex, &adapter);
			if(FAILED(r))
			{
				r = factory->EnumAdapters(0, &adapter);

				if(FAILED(r))
				{
					return false;
				}
			}

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Init - DirectX
		bool GraphicsModule::initDirectX(EngineDescription& desc)
		{
			#pragma region SwapChain
			if (desc.Graphics.Fullscreen)
			{
				RECT rect;
				HWND hDesktop = GetDesktopWindow();
				GetWindowRect(hDesktop, &rect);

				desc.Graphics.Width = rect.right;
				desc.Graphics.Height = rect.bottom;
			}

			DXGI_SWAP_CHAIN_DESC swapDesc;
			ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

			swapDesc.BufferCount = 2;
			swapDesc.BufferDesc.Height = desc.Graphics.Height;
			swapDesc.BufferDesc.Width = desc.Graphics.Width;
			swapDesc.BufferDesc.RefreshRate.Denominator = 1;
			swapDesc.BufferDesc.RefreshRate.Numerator = 60;
			swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapDesc.OutputWindow = desc.Window.hWnd;
			swapDesc.SampleDesc.Count = 1;
			swapDesc.SampleDesc.Quality = 0;
			swapDesc.Windowed = !desc.Graphics.Fullscreen;
			swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			swapDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			
#if TIKI_DX10
			swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

			HRESULT r = D3D10CreateDeviceAndSwapChain(
				NULL,
				D3D10_DRIVER_TYPE_HARDWARE,
				NULL,
				0,
				D3D10_SDK_VERSION,
				&swapDesc,
				&swapChain,
				&device
			);
			deviceContext = device;
#else
			swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;

			D3D_FEATURE_LEVEL level;
			D3D_FEATURE_LEVEL levels = D3D_FEATURE_LEVEL_11_0;

			HRESULT r = D3D11CreateDeviceAndSwapChain(
				NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				D3D11_CREATE_DEVICE_DEBUG, //0, // DEBUG FLAG
				&levels,
				1,
				D3D11_SDK_VERSION,
				&swapDesc,
				&swapChain,
				&device,
				&level,
				&deviceContext
			);
#endif

			if (FAILED(r)) { return false; }

			DllMain::Device = device;
			DllMain::Context = deviceContext;
			#pragma endregion

			if (!initDirectXBackBuffer(desc)) return false;
			if (!initDirectXDepthStencil(desc)) return false;

			#pragma region DepthStencilState
#if TIKI_DX10
			D3D10_DEPTH_STENCIL_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

			depthStencilDesc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D10_COMPARISON_LESS_EQUAL;

			depthStencilDesc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

			depthStencilDesc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
#else
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
#endif

			depthStencilDesc.DepthEnable = true;
			depthStencilDesc.StencilEnable = true;
			depthStencilDesc.StencilReadMask = 0xFF;
			depthStencilDesc.StencilWriteMask = 0xFF;

			r = device->CreateDepthStencilState(
				&depthStencilDesc,
				&depthStencilState
			);
			deviceContext->OMSetDepthStencilState(depthStencilState, 1);

			if (FAILED(r)) { return false; }
			#pragma endregion

			#pragma region RasterizerState
#if TIKI_DX10
			D3D10_RASTERIZER_DESC rasterDesc;

			rasterDesc.CullMode = D3D10_CULL_NONE;
			rasterDesc.FillMode = D3D10_FILL_SOLID;
#else
			D3D11_RASTERIZER_DESC rasterDesc;

			rasterDesc.CullMode = D3D11_CULL_NONE;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
#endif

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = true;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;
			
			r = device->CreateRasterizerState(
				&rasterDesc,
				&rasterStateBackfaces
			);

			if(FAILED(r))
			{
				engine->HLog.WriteError("Can't create RasterizerState", 0);
			}

			deviceContext->RSSetState(rasterStateBackfaces); // No Culling
			#pragma endregion

			#pragma region DepthDisableStencil
#if TIKI_DX10
			D3D10_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
			ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));
#else
			D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
			ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));
#endif

			depthDisabledStencilDesc.DepthEnable = false;
			depthDisabledStencilDesc.StencilEnable = false;			

			r = device->CreateDepthStencilState(
				&depthDisabledStencilDesc,
				&depthStencilStateDisable
			);

			if (FAILED(r)) { this->Dispose(); return false; }
			#pragma endregion

			#pragma region BlendState
#if TIKI_DX10
			D3D10_BLEND_DESC blendStateDesc;
			ZeroMemory(&blendStateDesc, sizeof(blendStateDesc));

			blendStateDesc.BlendEnable[0] = TRUE;
			blendStateDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
			blendStateDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
			blendStateDesc.BlendOp = D3D10_BLEND_OP_ADD;
			blendStateDesc.SrcBlendAlpha = D3D10_BLEND_ONE;
			blendStateDesc.DestBlendAlpha = D3D10_BLEND_INV_SRC_ALPHA;
			blendStateDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
			blendStateDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
#else
			D3D11_BLEND_DESC blendStateDesc;
			ZeroMemory(&blendStateDesc, sizeof(blendStateDesc));

			blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
			blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
#endif
			
			r = device->CreateBlendState(
				&blendStateDesc,
				&blendStateInterface
			);

			if (FAILED(r)) { this->Dispose(); return false; }
			

            ZeroMemory(&blendStateDesc, sizeof(blendStateDesc));

#if TIKI_DX10
			blendStateDesc.BlendEnable[0] = TRUE;
			blendStateDesc.SrcBlend = D3D10_BLEND_SRC_ALPHA;
			blendStateDesc.DestBlend = D3D10_BLEND_INV_SRC_ALPHA;
			blendStateDesc.BlendOp = D3D10_BLEND_OP_ADD;
			blendStateDesc.SrcBlendAlpha = D3D10_BLEND_SRC_ALPHA;
			blendStateDesc.DestBlendAlpha = D3D10_BLEND_INV_SRC_ALPHA;
			blendStateDesc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
			blendStateDesc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
#else
			blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
			blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
#endif

			r = device->CreateBlendState(
                &blendStateDesc,
                &blendStateParticle
            );

            if (FAILED(r)) { this->Dispose(); return false; }
            #pragma endregion

			if (!initDirectXViewPort(desc)) return false;

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Init - DirectX - BackBuffer
		bool GraphicsModule::initDirectXBackBuffer(EngineDescription& desc)
		{
			TDX_Texture2D* backBufferPtr;
			HRESULT r = swapChain->GetBuffer(0, __uuidof(TDX_Texture2D), (void**)&backBufferPtr);

			if (FAILED(r)) { return false; }

			r = device->CreateRenderTargetView(backBufferPtr, NULL, &renderTargetView);
			backBufferPtr->Release();

			if (FAILED(r)) { return false; }

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Init - DirectX - DepthStencil
		bool GraphicsModule::initDirectXDepthStencil(EngineDescription& desc)
		{
#if TIKI_DX10
			D3D10_TEXTURE2D_DESC depthDesc;
			ZeroMemory(&depthDesc, sizeof(depthDesc));

			depthDesc.Format =  DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthDesc.Usage = D3D10_USAGE_DEFAULT;
			depthDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
#else
			D3D11_TEXTURE2D_DESC depthDesc;
			ZeroMemory(&depthDesc, sizeof(depthDesc));

			depthDesc.Format =  DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthDesc.Usage = D3D11_USAGE_DEFAULT;
			depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
#endif

			depthDesc.Width = desc.Graphics.Width;
			depthDesc.Height = desc.Graphics.Height;
			depthDesc.MipLevels = 1;
			depthDesc.ArraySize = 1;
			depthDesc.SampleDesc.Count = 1;
			depthDesc.SampleDesc.Quality = 0;
			depthDesc.CPUAccessFlags = 0;
			depthDesc.MiscFlags = 0;

			HRESULT r = device->CreateTexture2D(
				&depthDesc,
				NULL,
				&depthStencilBuffer
			);

			if (FAILED(r)) { return false; }

#if TIKI_DX10
			D3D10_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
			ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

			depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilViewDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
#else
			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
			ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

			depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
#endif

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

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Init - DirectX - ViewPort
		bool GraphicsModule::initDirectXViewPort(EngineDescription& desc)
		{
#if TIKI_DX10
			D3D10_VIEWPORT viewPort;
			ZeroMemory(&viewPort, sizeof(viewPort));

			viewPort.Width = desc.Graphics.Width;
			viewPort.Height = desc.Graphics.Height;
#else
			D3D11_VIEWPORT viewPort;
			ZeroMemory(&viewPort, sizeof(viewPort));

			viewPort.Width = (float)desc.Graphics.Width;
			viewPort.Height = (float)desc.Graphics.Height;
#endif

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
	}
}
