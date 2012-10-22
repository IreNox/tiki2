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

#include "Core/DrawArgs.h"

#include "Core/Camera.h"
#include "Core/GameObject.h"

#include <ctime>
#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		GraphicsModule::GraphicsModule(Engine* engine)
			: IGraphics(engine), inited(false), indexBuffer(0), vertexBuffers(), rasterStateBackfaces(0), device(0),
			deviceContext(0), depthStencilState(0), depthStencilView(0), renderTargetView(0), rtScreen(0), rtBackBuffer(0),
			renderTargets(), postProcesses(), postProcessPassQuads(), defaultPostProcess(0), currentArgs(DrawArgs::Empty),
			depthStencilStateDisable(0), screenSizeRenderTargets(), factory(0), adapter(0), swapChain(0), depthStencilBuffer(0),
			cbufferLights(0), cbufferCamera(0), cbufferObject(0), blendStateAlphaBlend(0), blendStateAlphaBlendDisabled(0)
		{
			clearColor = Color::TikiBlue;
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

			SafeRelease(&indexBuffer);

			auto values = vertexBuffers.GetValues();
			for (UInt32 i = 0; i < values->Count(); i++)
			{
				VertexBuffer* buffer = values->Get(i);

				SafeRelease(&buffer);
			}
			delete(values);

			SafeRelease(&rtDepth);
			SafeRelease(&rtNormal);
			SafeRelease(&rtScreen);
			SafeRelease(&rtBackBuffer);

			this->RemovePostProcess(defaultPostProcess);

			UInt32 i = 0;
			while (i < postProcesses.Count())
			{
				this->RemovePostProcess(postProcesses[i]);
				i++;
			}

#if _DEBUG
			SafeRelease(&lineRenderer);
#endif

			SafeDelete(&cbufferLights);
			SafeDelete(&cbufferCamera);
			SafeDelete(&cbufferObject);

			SafeRelease(&blendStateAlphaBlend);
			SafeRelease(&blendStateAlphaBlendDisabled);
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

			wstring path = HelperPath::CombineWorkingPath(wstring(L"Screenshots/") + fileName);

			rtBackBuffer->SaveToFile(path.c_str());

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
				HelperLog::Write("Warning: Can't resize BackTarget.");
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
			//	HelperLog::Write("Warning: Can't change Fullscreen mode.");
			//}

			if (FAILED(r))
			{
				HelperLog::Write("Warning: Can't resize BackBuffer.");
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

		IRenderTarget* GraphicsModule::GetDepthTarget()
		{
			return rtDepth;
		}

		IRenderTarget* GraphicsModule::GetNormalTarget()
		{
			return rtNormal;
		}

		IRenderTarget* GraphicsModule::GetScreenTarget()
		{
			return rtScreen;
		}
		#pragma endregion

		#pragma region Member - Get - Buffer
		IndexBuffer* GraphicsModule::GetIndexBuffer()
		{
			return indexBuffer;
		}

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

		void GraphicsModule::SetStateAlphaBlend(bool value)
		{			
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

			if (value)
			{
				deviceContext->OMSetBlendState(blendStateAlphaBlend, blendFactor, 0xffffffff);
			}
			else
			{
				deviceContext->OMSetBlendState(blendStateAlphaBlendDisabled, blendFactor, 0xffffffff);
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
			lineRenderer->DrawLine(start, end, color);
		}

		void GraphicsModule::DrawLine(List<Vector3>* points, const Color& color, bool lastToFirst)
		{
			lineRenderer->DrawLine(points, color, lastToFirst);
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

			rtScreen->Apply(0);
			rtScreen->Clear(clearColor);
			this->SetStateDepthEnabled(true);
			deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
						
			rtDepth->Clear(Color::Black);
			rtDepth->Apply(1);
			rtNormal->Clear(Color::NormalDefault);
			rtNormal->Apply(2);

			if (args.CurrentCamera)
			{
				CBMatrices* matrices = cbufferCamera->Map();
				*matrices = *args.CurrentCamera->GetMatrices();
				cbufferCamera->Unmap();
			}

#if _DEBUG
			lineRenderer->Begin();
#endif
		}

		void GraphicsModule::End()
		{
			deviceContext->OMSetDepthStencilState(depthStencilStateDisable, 1);

#if _DEBUG
			lineRenderer->End();
#endif

			UInt32 i = 0;
			while (i < postProcesses.Count())
			{
				drawPostProcess(postProcesses[i]);

				i++;
			}
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
			defaultPostProcess->GetPasses()->Get(0)->AddInput(varName, target);
		}

		void GraphicsModule::RemovePostProcess(PostProcess* postProcess)
		{
			postProcesses.Remove(postProcess);

			const List<PostProcessPass*>* passes = postProcess->GetPasses();

			UInt32 i = 0;
			while (i < passes->Count())
			{
				PostProcessPass* pass = passes->Get(i);

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
				HelperLog::WriteError("Can't create RasterizerState", 0);
			}

			deviceContext->RSSetState(rasterStateBackfaces); // back face culling
			#pragma endregion

			#pragma region DepthDisableStencil
			D3D11_DEPTH_STENCIL_DESC depthDisabledStencilDesc;
			ZeroMemory(&depthDisabledStencilDesc, sizeof(depthDisabledStencilDesc));

			depthDisabledStencilDesc.DepthEnable = false;
			depthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
			depthDisabledStencilDesc.StencilEnable = true;
			depthDisabledStencilDesc.StencilReadMask = 0xFF;
			depthDisabledStencilDesc.StencilWriteMask = 0xFF;
			depthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			depthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			r = device->CreateDepthStencilState(
				&depthDisabledStencilDesc,
				&depthStencilStateDisable
				);

			if (FAILED(r)) { this->Dispose(); return false; }
			#pragma endregion

			#pragma region BlendState
			D3D11_BLEND_DESC blendStateDesc;
			ZeroMemory(&blendStateDesc, sizeof(blendStateDesc));

			blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
			blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
			blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
			blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
			blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
			blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;

			r = device->CreateBlendState(
				&blendStateDesc,
				&blendStateAlphaBlend
			);

			if (FAILED(r)) { this->Dispose(); return false; }

			ZeroMemory(&blendStateDesc, sizeof(blendStateDesc));
			blendStateDesc.RenderTarget[0].BlendEnable = FALSE;

			r = device->CreateBlendState(
				&blendStateDesc,
				&blendStateAlphaBlendDisabled
			);

			if (FAILED(r)) { this->Dispose(); return false; }

			this->SetStateAlphaBlend(true);
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
			this->indexBuffer = new IndexBuffer(engine);

			this->cbufferLights = new ConstantBuffer<CBLights>(engine);
			this->cbufferCamera = new ConstantBuffer<CBMatrices>(engine);
			this->cbufferObject = new ConstantBuffer<CBObjectData>(engine);

			this->rtBackBuffer = new RenderTarget(engine, renderTargetView);

			this->rtScreen = new RenderTarget(engine);
			this->rtScreen->CreateScreenSize();

			this->rtNormal = new RenderTarget(engine);
			this->rtNormal->CreateScreenSize();

			this->rtDepth = new RenderTarget(engine);
			this->rtDepth->CreateScreenSize();

			IShader* shader = new Shader(engine);
			shader->LoadFromFile(L"Data/Effects/pp_default.fx");

			PostProcessPass* pass = new PostProcessPass(engine, shader);
			pass->AddInput("rtScreen", rtScreen);
			pass->AddInput("rtNormal", rtNormal);
			//pass->AddInput("rtDepth", rtDepth);
			pass->AddOutput(0, rtBackBuffer);

			defaultPostProcess = new PostProcess(engine);
			defaultPostProcess->AddPass(pass);

			SafeRelease(&pass);
			SafeRelease(&shader);

#if _DEBUG
			lineRenderer = new DebugLineRenderer(engine);
#endif

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Draw - PostProcess
		void GraphicsModule::drawPostProcess(PostProcess* postProcess)
		{
			const List<PostProcessPass*>* passes = postProcess->GetPasses();

			UInt32 i = 0;
			while (i < passes->Count())
			{
				PostProcessPass* pass = passes->Get(i);
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
			CBLights* buf = cbufferLights->Map();
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
				buf->Data[i].Direction = l->GetGameObject()->PRS.GRotation() * Vector3::ForwardRH;

				i++;
			}

			cbufferLights->Unmap();
		}
		#pragma endregion
	}
}
