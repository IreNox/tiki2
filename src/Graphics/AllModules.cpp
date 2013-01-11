#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include "Core/Engine.h"
#include "Core/IContentManager.h"

#include "Core/HelperLog.h"
#include "Core/HelperPath.h"

#include "Graphics/GraphicsModule.h"
#include "Graphics/SpriteBatchModule.h"
#include "Graphics/DllMain.h"

#include "Graphics/PPDefault.h"

#include "Core/DrawArgs.h"

#include "Core/Camera.h"
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
		#pragma region GraphicsModule
		#pragma region Class
		GraphicsModule::GraphicsModule(Engine* engine)
			: IGraphics(engine), inited(false), rasterStateBackfaces(0), device(0), blendStateParticle(0),  blendStateInterface(0),
			deviceContext(0), depthStencilState(0), depthStencilView(0), renderTargetView(0), rtBackBuffer(0),
			renderTargets(), postProcesses(), postProcessPassQuads(), defaultPostProcess(0), currentArgs(DrawArgs::Empty),
			depthStencilStateDisable(0), screenSizeRenderTargets(), factory(0), adapter(0), swapChain(0), depthStencilBuffer(0),
			cbufferLights(0), cbufferCamera(0), cbufferObject(0), rtScreenIndex(0), defaultPostProcessPass(0)
#if _DEBUG
			, debugConsole(0), debugLineRenderer(0)
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

			SafeRelease(&rtInterface);
			SafeRelease(&rtDepth);
			SafeRelease(&rtNormal);
			SafeRelease(&rtLight);
			SafeRelease(&rtScreen[0]);
			SafeRelease(&rtScreen[1]);
			SafeRelease(&rtBackBuffer);

			SafeRelease(&defaultPostProcessPass);
			this->RemovePostProcess(defaultPostProcess);

			UInt32 i = 0;
			while (i < postProcesses.Count())
			{
				this->RemovePostProcess(postProcesses[i]);
				i++;
			}

#if _DEBUG
			SafeRelease(&debugConsole);
			SafeRelease(&debugLineRenderer);
#endif

			SafeDelete(&cbufferLights);
			SafeDelete(&cbufferCamera);
			SafeDelete(&cbufferObject);

			SafeRelease(&blendStateParticle);
            SafeRelease(&blendStateInterface);

			SafeRelease(&depthStencilState);
			SafeRelease(&depthStencilStateDisable);
			SafeRelease(&rasterStateBackfaces);

			SafeRelease(&depthStencilView);
			SafeRelease(&depthStencilBuffer);
			SafeRelease(&renderTargetView);
			SafeRelease(&deviceContext);
			SafeRelease(&device);
			SafeRelease(&swapChain);

			SafeRelease(&adapter);
			SafeRelease(&factory);

			inited = false;
		}
		#pragma endregion

		#pragma region Member
		IConstantBuffer* GraphicsModule::CreateConstantBuffer(UInt32 size)
		{
			return new ConstantBuffer<Byte>(engine, size);
		}

		void GraphicsModule::SwitchScreenTarget(IRenderTarget** inputTarget, IRenderTarget** outputTarget)
		{
			*inputTarget = rtScreen[rtScreenIndex];
			*outputTarget = rtScreen[!rtScreenIndex];

			rtScreenIndex = !rtScreenIndex;
		}

		void GraphicsModule::MakeScreenshot(wcstring fileName)
		{
			bool newName = false;
			if (fileName == 0)
			{
				time_t now = time(0);

				tm time;
				localtime_s(&time, &now);

				wostringstream s;
				s << L"Screenshot-" << (time.tm_year + 1900) << "-" << (time.tm_mon + 1) << "-" << time.tm_mday << "-" << time.tm_hour << "-" << time.tm_min << "-" << time.tm_sec << ".dds";

				wchar_t* fileName2 = new wchar_t[s.str().length() + 1];
				memcpy(fileName2, s.str().c_str(), sizeof(wchar_t) * (s.str().length() + 1));

				fileName = fileName2;
				newName = true;
			}

			wstring path = engine->HPath.CombineWorkingPath(wstring(L"Screenshots/") + fileName);

			rtBackBuffer->SaveToFile(
				path.c_str()
			);

			//IRenderTarget* oldTarget = defaultPostProcess->GetPasses()->Get(0)->GetOutput()->Get(0);
			//
			//IRenderTarget* target = new RenderTarget(engine);
			//target->CreateScreenSize(true);
			//defaultPostProcess->GetPasses()->Get(0)->SetOutput(0, target);

			//drawPostProcess(defaultPostProcess);

			//defaultPostProcess->GetPasses()->Get(0)->SetOutput(0, oldTarget);

			//UInt32 len = 0;
			//void* data = 0;
			//target->GetData(PF_A8R8G8B8, &data, &len);

			//FileStream stream(fileName, FileMode::FM_Write);
			//stream.Write(data, 0, len);

			if (newName)
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

			ID3D11Texture2D* backBuffer;
			swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
			while (backBuffer->Release()) {}

			r = swapChain->ResizeBuffers(
				0,
				desc.Graphics.Width,
				desc.Graphics.Height,
				DXGI_FORMAT_UNKNOWN,
				DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH
			);

			//r = swapChain->SetFullscreenState(desc.Graphics.Fullscreen, NULL);

			//if (FAILED(r))
			//{
			//	engine->HLog.Write("Warning: Can't change Fullscreen mode.");
			//}

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

		#pragma region Member - Get - Buffer
		ConstantBuffer<CBLights>* GraphicsModule::GetCBufferLight()
		{
			return cbufferLights;
		}

		ConstantBuffer<CBMatrices>* GraphicsModule::GetCBufferCamera()
		{
			return cbufferCamera;
		}

		ConstantBuffer<CBObjectData>* GraphicsModule::GetCBufferObject()
		{
			return cbufferObject;
		}
		#pragma endregion

		#pragma region Member - Set
		void GraphicsModule::SetRenderTarget(UInt32 slot, ID3D11RenderTargetView* target)
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

		void GraphicsModule::SetFirstAndOnlyRenderTargets(ID3D11RenderTargetView* target)
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

		void GraphicsModule::DrawConsole(const DrawArgs& args)
		{
			debugConsole->Update(args.Update);
			debugConsole->Draw(args);
		}
#endif
		#pragma endregion

		#pragma region Member - Begin/End
		void GraphicsModule::Begin(DrawArgs& args)
		{
			currentArgs = args;

			if (args.Lights.IsDirty) // || args.Lights.Properties.IsDirty)
			{
				setLightChanged(args);
				args.Lights.IsDirty = false;
				//args.Lights.Properties.IsDirty = false;
			}

			defaultPostProcessPass->SetOutput(
				0,
				(args.CurrentCamera != 0 && args.CurrentCamera->GetRenderTarget() != 0 ? args.CurrentCamera->GetRenderTarget() : rtBackBuffer)
			);

			rtInterface->Clear(Color::TransparentBlack);
			rtScreen[rtScreenIndex]->Apply(0);
			rtScreen[rtScreenIndex]->Clear(clearColor);
			this->SetStateDepthEnabled(true);
			deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
						
			rtDepth->Clear(Color::Black);
			rtDepth->Apply(1);
			rtNormal->Clear(Color::Black);
			rtNormal->Apply(2);
			rtLight->Clear(Color::TransparentBlack);
			rtLight->Apply(3);

			if (args.CurrentCamera)
			{
				CBMatrices* matrices = cbufferCamera->MapTI();
				*matrices = args.CurrentCamera->GetMatrices();
				cbufferCamera->Unmap();
			}

			deviceContext->RSSetState(rasterStateBackfaces);

#if _DEBUG
			debugLineRenderer->Begin();
#endif
		}

		void GraphicsModule::End()
		{
			this->SetStateDepthEnabled(false);

#if _DEBUG
			debugLineRenderer->End();
#endif

			this->SetStateAlphaBlend(BSM_Disable);

			UInt32 i = 0;
			while (i < postProcesses.Count())
			{
				drawPostProcess(postProcesses[i]);

				i++;
			}
			defaultPostProcessPass->SetInput("rtScreen", rtScreen[rtScreenIndex]);
			drawPostProcess(defaultPostProcess);

			swapChain->Present(0, 0);
		}
		#pragma endregion

		#pragma region Member - Add/Remove
		void GraphicsModule::AddPostProcess(PostProcess* postProcess)
		{
			postProcesses.Add(postProcess);
			SafeAddRef(&postProcess);
		}

		void GraphicsModule::AddDefaultProcessTarget(cstring varName, IRenderTarget* target)
		{
			defaultPostProcessPass->AddInput(varName, target);
		}

		void GraphicsModule::RemovePostProcess(PostProcess* postProcess)
		{
			postProcesses.Remove(postProcess);

			const List<PostProcessPass*>& passes = postProcess->GetPasses();

			UInt32 i = 0;
			while (i < passes.Count())
			{
				PostProcessPass* pass = passes[i];

				if (postProcessPassQuads.ContainsKey(pass))
				{
					Quad* quad = postProcessPassQuads[pass];
					SafeRelease(&quad);

					postProcessPassQuads.Remove(pass);
				}

				i++;
			}

			SafeRelease(&postProcess);
		}

		void GraphicsModule::AddScreenSizeRenderTarget(RenderTarget* target)
		{
			screenSizeRenderTargets.Add(target);
		}

		void GraphicsModule::RemoveScreenSizeRenderTarget(RenderTarget* target)
		{
			screenSizeRenderTargets.Remove(target);
		}
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
			swapDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
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

			DllMain::Device = device;
			DllMain::Context = deviceContext;
			#pragma endregion

			if (!initDirectXBackBuffer(desc)) return false;
			if (!initDirectXDepthStencil(desc)) return false;

			#pragma region DepthStencilState
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

			depthStencilDesc.DepthEnable = true;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

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
			#pragma endregion

			#pragma region RasterizerState
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
				&rasterStateBackfaces
			);

			if(FAILED(r))
			{
				engine->HLog.WriteError("Can't create RasterizerState", 0);
			}

			deviceContext->RSSetState(rasterStateBackfaces); // No Culling
			#pragma endregion

			#pragma region DepthDisableStencil
			D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
			ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

			depthDisabledStencilDesc.DepthEnable = false;
			depthDisabledStencilDesc.StencilEnable = false;

			r = device->CreateDepthStencilState(
				&depthDisabledStencilDesc,
				&depthStencilStateDisable
			);

			if (FAILED(r)) { this->Dispose(); return false; }
			#pragma endregion

			#pragma region BlendState
			D3D11_BLEND_DESC blendStateDesc;
			ZeroMemory(&blendStateDesc, sizeof(blendStateDesc));

			// GUT!!
			blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
			blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


			r = device->CreateBlendState(
				&blendStateDesc,
				&blendStateInterface
			);

			if (FAILED(r)) { this->Dispose(); return false; }
			

            ZeroMemory(&blendStateDesc, sizeof(blendStateDesc));

            // GUT!!
            blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
            blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
            blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
            blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
            blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
            blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
            blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
            blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;


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
			ID3D11Texture2D* backBufferPtr;
			HRESULT r = swapChain->GetBuffer(
				0,
				__uuidof(ID3D11Texture2D),
				(LPVOID*)&backBufferPtr
			);

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
			D3D11_TEXTURE2D_DESC depthDesc;
			ZeroMemory(&depthDesc, sizeof(depthDesc));

			depthDesc.Width = desc.Graphics.Width;
			depthDesc.Height = desc.Graphics.Height;
			depthDesc.MipLevels = 1;
			depthDesc.ArraySize = 1;
			depthDesc.Format =  DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthDesc.SampleDesc.Count = 1;
			depthDesc.SampleDesc.Quality = 0;
			depthDesc.Usage = D3D11_USAGE_DEFAULT;
			depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthDesc.CPUAccessFlags = 0;
			depthDesc.MiscFlags = 0;

			HRESULT r = device->CreateTexture2D(
				&depthDesc,
				NULL,
				&depthStencilBuffer
				);

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

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Init - DirectX - ViewPort
		bool GraphicsModule::initDirectXViewPort(EngineDescription& desc)
		{
			D3D11_VIEWPORT viewPort = D3D11_VIEWPORT();
			ZeroMemory(&viewPort, sizeof(viewPort));

			viewPort.Width = (float)desc.Graphics.Width;
			viewPort.Height = (float)desc.Graphics.Height;
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
			this->cbufferLights = new ConstantBuffer<CBLights>(engine);
			this->cbufferCamera = new ConstantBuffer<CBMatrices>(engine);
			this->cbufferObject = new ConstantBuffer<CBObjectData>(engine);

			this->rtBackBuffer = new RenderTarget(engine, renderTargetView, false);
			this->rtBackBuffer->AddRef();

			this->rtScreen[0] = new RenderTarget(engine);
			this->rtScreen[0]->CreateScreenSize(false, PF_R8G8B8A8);
			this->rtScreen[0]->AddRef();

			this->rtScreen[1] = new RenderTarget(engine);
			this->rtScreen[1]->CreateScreenSize(false, PF_R8G8B8A8);
			this->rtScreen[1]->AddRef();

			this->rtLight = new RenderTarget(engine);
			this->rtLight->CreateScreenSize(false, PF_R8G8B8A8);
			this->rtLight->AddRef();

			this->rtInterface = new RenderTarget(engine);
			this->rtInterface->CreateScreenSize(false, PF_R8G8B8A8);
			this->rtInterface->AddRef();

			this->rtNormal = new RenderTarget(engine);
			this->rtNormal->CreateScreenSize();
			this->rtNormal->AddRef();

			this->rtDepth = new RenderTarget(engine);
			this->rtDepth->CreateScreenSize();
			this->rtDepth->AddRef();

			defaultPostProcess = new PPDefault(engine, rtBackBuffer);
			defaultPostProcess->AddRef();

			defaultPostProcessPass = defaultPostProcess->GetPasses()[3];
			defaultPostProcessPass->AddRef();

#if _DEBUG
			debugConsole = new DebugConsole(engine);
			debugLineRenderer = new DebugLineRenderer(engine);
#endif

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Draw - PostProcess
		void GraphicsModule::drawPostProcess(PostProcess* postProcess)
		{
			const List<PostProcessPass*>& passes = postProcess->GetPasses();

			UInt32 i = 0;
			while (i < passes.Count())
			{
				PostProcessPass* pass = passes[i];
				Quad* quad = 0;

				if (!postProcessPassQuads.ContainsKey(pass))
				{
					quad = new Quad(engine);
					quad->SetShader(pass->GetShader());
					postProcessPassQuads.Add(pass, quad);
				}
				else
				{
					quad = postProcessPassQuads[pass];
				}

				postProcess->UpdatePass(i, currentArgs);
				pass->UpdateVars(currentArgs);

				quad->SetOutput(pass->GetOutput());				
				quad->SetInput(pass->GetInput());

				quad->Draw();

				i++;
			}
		}
		#pragma endregion

		#pragma region Private Member - Set - Lights
		void GraphicsModule::setLightChanged(const DrawArgs& args)
		{
			CBLights* buf = cbufferLights->MapTI();
			buf->Props = args.Lights.Properties;

			buf->Count = (float)args.Lights.SceneLights->Count();
			if (buf->Count > 32) buf->Count = 32;

			UInt32 i = 0;
			while (i < buf->Count)
			{
				Light* l = args.Lights.SceneLights->Get(i);

				buf->Data[i].Range = l->GetRange();
				buf->Data[i].Color = l->GetColor().ToVector4();
				buf->Data[i].Position = l->GetGameObject()->PRS.GPosition();
				buf->Data[i].Direction = l->GetGameObject()->PRS.GRotation() * Vector3::Forward;

				i++;
			}

			cbufferLights->Unmap();
		}
		#pragma endregion
		#pragma endregion

		#pragma region SpriteBatchModule
		#pragma region Class
		SpriteBatchModule::SpriteBatchModule(Engine* engine)
			: ISpriteBatch(engine), shader(0), declaration(0), buffer(0)
		{
		}

		SpriteBatchModule::~SpriteBatchModule()
		{

		}
		#pragma endregion

		#pragma region Member - Init/Dispose
		bool SpriteBatchModule::Initialize(EngineDescription& desc)
		{
			shader = (Shader*)engine->content->LoadShader(L"os_spritebatch");
			shader->AddRef();

			declaration = new VertexDeclaration(
				engine,
				shader,
				SpriteBatchVertex::Declaration,
				SpriteBatchVertex::DeclarationCount
			);

			buffer = new DynamicBuffer<SpriteBatchVertex, D3D11_BIND_VERTEX_BUFFER>(engine);

			engine->graphics->ScreenSizeChanged.AddHandler(this);
			this->Handle(engine->graphics, ScreenSizeChangedArgs(engine->graphics, engine->graphics->GetViewPort()));

			return true;
		}

		void SpriteBatchModule::Dispose()
		{
			SafeRelease(&buffer);
			SafeRelease(&shader);
			SafeRelease(&declaration);
		}
		#pragma endregion

		#pragma region Member - Begin/End
		void SpriteBatchModule::Begin()
		{			
			spriteInfos.Clear();
			spriteVertices.Clear();
		}

		void SpriteBatchModule::End()
		{
			if (spriteInfos.Count() == 0) return;
			spriteInfos.Sort();

			DllMain::ModuleGraphics->SetStateAlphaBlend(BSM_Interface);
			DllMain::ModuleGraphics->GetInterfaceTarget()->ApplyFirstAndOnly();

			SpriteBatchVertex* vertices = buffer->Map(spriteVertices.Count());
			memcpy(vertices, spriteVertices.GetInternalData(), sizeof(SpriteBatchVertex) * spriteVertices.Count());
			buffer->Unmap();

			UINT offset = 0;
			UINT stride = declaration->GetElementSize();

			declaration->Apply();

			ID3D11Buffer* vertexBuffer = this->buffer->GetBuffer();
			DllMain::Context->IASetVertexBuffers(
				0,
				1,
				&vertexBuffer,
				&stride,
				&offset
			);

			UInt32 i = 0;
			Sprite& info = Sprite();
			while (i < spriteInfos.Count())
			{
				info = spriteInfos.GetRef(i);

				DllMain::Context->IASetPrimitiveTopology(
					(info.Lines ? D3D11_PRIMITIVE_TOPOLOGY_LINELIST : D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)				
				);

				shader->SetSingle("value", info.Value);
				if (info.Texture != 0) shader->SetTexture("tex", info.Texture);
				shader->Apply();

				DllMain::Context->Draw(info.VertexCount, info.BufferIndex);

				i++;
			}

			DllMain::ModuleGraphics->SetStateAlphaBlend(BSM_Disable);
		}
		#pragma endregion

		#pragma region Member - Draw
		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position)
		{
			Vector3 tl = transformPoint(
				Vector3(position.X, position.Y, 0.0f)
			);

			Vector2 br = Vector2(
				tl.X + texture->GetWidth(),
				tl.Y - texture->GetHeight()
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, 0.0f),
				Vector3(tl.X, br.Y, 0.0f),
				Vector3(br.X, br.Y, 0.0f),
				Vector4(0.0f, 0.0f, 1.0f, 1.0f),
				Color::White
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Rectangle& destRect)
		{
			Vector3 tl = transformPoint(
				Vector3(
				(float)destRect.X,
				(float)destRect.Y,
				0.0f
				)
			); 

			Vector3 br = Vector3(
				tl.X + destRect.Width,
				tl.Y - destRect.Height,
				0.0f
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, 0.0f),
				Vector3(tl.X, br.Y, 0.0f),
				br,
				Vector4(0.0f, 0.0f, 1.0f, 1.0f),
				Color::White
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Rectangle& destRect, const Rectangle& srcRect)
		{
			Vector3 tl = transformPoint(
				Vector3(
					(float)destRect.X,
					(float)destRect.Y,
					1.0f
				)
			); 

			Vector3 br = Vector3(
				tl.X + destRect.Width,
				tl.Y - destRect.Height,
				-1.0f
			);

			Vector2 size = texture->GetSize();

			Vector4 texCorrd = Vector4(
				(float)srcRect.X / size.X,
				(float)srcRect.Y / size.Y,
				(float)(srcRect.X + srcRect.Width) / size.X,
				(float)(srcRect.Y + srcRect.Height) / size.Y
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, -1.0f),
				Vector3(tl.X, br.Y, -1.0f),
				br,
				texCorrd,
				Color::White
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect, const Color& color)
		{
			this->Draw(texture, destRect, texture->GetRectangle(), color, 1.0f);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect, const Color& color, float layerDepth)
		{
			this->Draw(texture, destRect, texture->GetRectangle(), color, layerDepth);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect, const RectangleF& srcRect, const Color& color)
		{
			this->Draw(texture, destRect, srcRect, color, 1.0f);			
		}

		void SpriteBatchModule::Draw(ITexture* texture, const RectangleF& destRect, const RectangleF& srcRect, const Color& color, float layerDepth)
		{
			Vector3 tl = transformPoint(
				Vector3(destRect.X, destRect.Y, layerDepth)
			); 

			Vector3 br = Vector3(
				tl.X + destRect.Width,
				tl.Y - destRect.Height,
				-layerDepth
			);

			Vector2 size = texture->GetSize();

			Vector4 texCorrd = Vector4(
				srcRect.X / size.X,
				srcRect.Y / size.Y,
				(srcRect.X + srcRect.Width) / size.X,
				(srcRect.Y + srcRect.Height) / size.Y
			);

			drawInternal(
				texture,
				tl,
				Vector3(br.X, tl.Y, -layerDepth),
				Vector3(tl.X, br.Y, -layerDepth),
				br,
				texCorrd,
				color
			);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth)
		{
			this->Draw(texture, position, rotation, origin, Vector2(scale), layerDepth, Color::White);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth)
		{
			this->Draw(texture, position, rotation, origin, scale, layerDepth, Color::White);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth, const Color& color)
		{
			this->Draw(texture, position, rotation, origin, Vector2(scale),	layerDepth, color);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth, const Color& color)
		{
			this->Draw(texture, position, rotation, origin, scale,layerDepth, color, 0.0f);
		}

		void SpriteBatchModule::Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth, const Color& color, float value)
		{
			Vector3 origin3 = Vector3(origin, 0);
			Vector3 size = Vector3(texture->GetSize(), 0);

			Vector3 tl = Vector3(0.0f,   0.0f,   0.0f) - origin3;
			Vector3 tr = Vector3(size.X, 0.0f,   0.0f) - origin3;
			Vector3 bl = Vector3(0.0f,   size.Y, 0.0f) - origin3;
			Vector3 br = Vector3(size.X, size.Y, 0.0f) - origin3;

			tl = Vector3(tl.X * scale.X, tl.Y * scale.Y, layerDepth);
			tr = Vector3(tr.X * scale.X, tr.Y * scale.Y, layerDepth);
			bl = Vector3(bl.X * scale.X, bl.Y * scale.Y, layerDepth);
			br = Vector3(br.X * scale.X, br.Y * scale.Y, layerDepth);

			Quaternion rot = Quaternion::CreateFromYawPitchRoll(0, 0, rotation);
			tl = rot * tl;
			tr = rot * tr;
			bl = rot * bl;
			br = rot * br;

			Vector3 position3 = Vector3(position, 0.0f);
			tl = transformPoint(tl + position3);
			tr = transformPoint(tr + position3);
			bl = transformPoint(bl + position3);
			br = transformPoint(br + position3);

			drawInternal(texture, tl, tr, bl, br, Vector4(0.0f, 0.0f, 1.0f, 1.0f), color, value);
		}
		#pragma endregion

		#pragma region Member - DrawLine/DrawString
		void SpriteBatchModule::DrawLine(const List<Vector2>& vertices, const Color& color, float layerDepth /* = 1.0f */, bool loop /* = false */)
		{
			Sprite info;
			info.Lines = true;
			info.Texture = 0;
			info.BufferIndex = spriteVertices.Count();
			info.VertexCount = 0;
			info.Value = 0;
			info.LayerDepth = layerDepth;

			UInt32 i = 0;
			UInt32 c = vertices.Count() - (loop ? 0 : 1);
			while (i < c)
			{
				Vector2 v1 = vertices[i];
				Vector2 v2 = vertices[(i < c - 1 ? i + 1 : 0)];

				SpriteBatchVertex vertex[2] = {
					{ v1.X, screenSize.Y - v1.Y, -layerDepth, -1.0f, -1.0f, color.R, color.G, color.B, color.A },
					{ v2.X, screenSize.Y - v2.Y, -layerDepth, -1.0f, -1.0f, color.R, color.G, color.B, color.A }
				};

				spriteVertices.AddRange(vertex, 0, 2);
				info.VertexCount += 2;

				i++;
			}

			spriteInfos.Add(info);
		}

		void SpriteBatchModule::DrawString(IFont* font, wstring text, const Vector2& position, const Color& color, float layerDepth)
		{
			UInt32 i = 0;
			float width = 0;
			Vector2 pos = position;
			while (i < text.length())
			{
				width = font->DrawChar(text[i], pos, color, layerDepth);

				pos.X += width;
				i++;
			}
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void SpriteBatchModule::Handle(IGraphics* graphics, const ScreenSizeChangedArgs& args)
		{
			screenSize = args.CurrentViewPort->GetSize();
			projMatrix = Matrix::CreateOrthographicOffCenter(screenSize.X,	screenSize.Y, 0.001f, 10.0f);

			shader->SetMatrix("SBProjM", projMatrix);
		}
		#pragma endregion

		#pragma region Private Member
		Vector3 SpriteBatchModule::transformPoint(const Vector3& point)
		{
			return Vector3(
				point.X,
				(screenSize.Y - point.Y),
				-point.Z
			);
		}

		void SpriteBatchModule::drawInternal(ITexture* texture, const Vector3& tl, const Vector3& tr, const Vector3& bl, const Vector3& br, const Vector4& texCoord, const Color& color, float value)
		{
			Sprite info;
			info.Lines = false;
			info.Texture = texture;
			info.BufferIndex = spriteVertices.Count();
			info.VertexCount = 4;
			info.Value = value;
			info.LayerDepth = tl.Z;
			spriteInfos.Add(info);

			SpriteBatchVertex vertex[4] = {
				{ bl.X, bl.Y, bl.Z, texCoord.X, texCoord.W, color.R, color.G, color.B, color.A }, // BL
				{ tl.X, tl.Y, tl.Z, texCoord.X, texCoord.Y, color.R, color.G, color.B, color.A }, // TL
				{ br.X, br.Y, br.Z, texCoord.Z, texCoord.W, color.R, color.G, color.B, color.A }, // BR
				{ tr.X, tr.Y, tr.Z, texCoord.Z, texCoord.Y, color.R, color.G, color.B, color.A }  // TR
			};
			spriteVertices.AddRange(vertex, 0, 4);
		}
		#pragma endregion
		#pragma endregion
	}
}
