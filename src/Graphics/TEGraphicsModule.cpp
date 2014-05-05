
#if TIKI_DX10 || TIKI_DX11
#include "Graphics/DXGraphicsModule.h"
#elif TIKI_OGL
#include "Graphics/OGLGraphicsModule.h"
#endif

#include "Core/Camera.h"
#include "Core/DrawArgs.h"
#include "Core/GameObject.h"

#include "Graphics/PPDefault.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Member
		IConstantBuffer* GraphicsModule::CreateConstantBuffer(UInt32 size)
		{
			return TIKI_NEW ConstantBuffer<Byte>(engine, size);
		}

		void GraphicsModule::SwitchScreenTarget(IRenderTarget** inputTarget, IRenderTarget** outputTarget)
		{
			*inputTarget = rtScreen[rtScreenIndex];
			*outputTarget = rtScreen[!rtScreenIndex];

			rtScreenIndex = !rtScreenIndex;
		}
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

			this->SetStateDepthEnabled(true);
#if TIKI_DX10
			deviceContext->ClearDepthStencilView(depthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
#elif TIKI_DX11
			deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
#elif TIKI_OGL
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
			glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
#endif

			rtDepth->Clear(Color::Black);
			rtNormal->Clear(Color::Black);
			rtLight->Clear(Color::TransparentBlack);
			rtScreen[rtScreenIndex]->Clear(clearColor);
			rtInterface->Clear(Color::TransparentBlack);

#if TIKI_DX10
//			ID3D10ShaderResourceView* textures[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
#elif TIKI_DX11
			ID3D11ShaderResourceView* textures[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
			deviceContext->PSSetShaderResources( 0u, 16u, textures );
#endif

			rtLight->Apply(3);
			rtDepth->Apply(1);
			rtNormal->Apply(2);
			rtScreen[rtScreenIndex]->Apply(0);

			if (args.CurrentCamera)
			{
				CBMatrices* matrices = cbufferCamera->MapTI();
				*matrices = args.CurrentCamera->GetMatrices();
				cbufferCamera->Unmap();
			}

#if TIKI_DX10 || TIKI_DX11
			deviceContext->RSSetState(rasterStateBackfaces);
#if _DEBUG
			debugLineRenderer->Begin();
#endif
#endif
		}

		void GraphicsModule::End()
		{
			this->SetStateDepthEnabled(false);
			this->SetStateAlphaBlend(BSM_Disable);

#if _DEBUG && (TIKI_DX10 || TIKI_DX11)
			debugLineRenderer->End();
#endif

			UInt32 i = 0;
			while (i < postProcesses.Count())
			{
				drawPostProcess(postProcesses[i]);

				i++;
			}
			defaultPostProcessPass->SetInput("rtScreen", rtScreen[rtScreenIndex]);
			drawPostProcess(defaultPostProcess);

#if TIKI_DX10 || TIKI_DX11
			swapChain->Present(0, 0);
#elif TIKI_OGL
			SwapBuffers(deviceContext);
#endif
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
					quad = TIKI_NEW Quad(engine, pass->GetShader());
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

				buf->Data[i].Color = l->GetColor().ToVector4();
				buf->Data[ i ].Position = Vector4( l->GetGameObject()->PRS.GPosition( ), l->GetRange() );
				buf->Data[i].Direction = Vector4( l->GetGameObject()->PRS.GRotation() * Vector3::Forward, 0.0f );

				i++;
			}

			cbufferLights->Unmap();
		}
		#pragma endregion

		#pragma region Private Member - Init - Engine
		bool GraphicsModule::initEngine(EngineDescription& desc)
		{
			this->cbufferLights = TIKI_NEW ConstantBuffer<CBLights>(engine);
			this->cbufferCamera = TIKI_NEW ConstantBuffer<CBMatrices>(engine);
			this->cbufferObject = TIKI_NEW ConstantBuffer<CBObjectData>(engine);

#if TIKI_DX10 || TIKI_DX11
			this->rtBackBuffer = TIKI_NEW RenderTarget(engine, renderTargetView, false);
#elif TIKI_OGL
			this->rtBackBuffer = TIKI_NEW RenderTarget(engine, 0);
#endif
			this->rtBackBuffer->AddRef();

			this->rtScreen[0] = TIKI_NEW RenderTarget(engine);
			this->rtScreen[0]->CreateScreenSize(false, PF_R8G8B8A8);
			this->rtScreen[0]->AddRef();

			this->rtScreen[1] = TIKI_NEW RenderTarget(engine);
			this->rtScreen[1]->CreateScreenSize(false, PF_R8G8B8A8);
			this->rtScreen[1]->AddRef();

			this->rtLight = TIKI_NEW RenderTarget(engine);
			this->rtLight->CreateScreenSize(false, PF_R8G8B8A8);
			this->rtLight->AddRef();

			this->rtInterface = TIKI_NEW RenderTarget(engine);
			this->rtInterface->CreateScreenSize(false, PF_R8G8B8A8);
			this->rtInterface->AddRef();

			this->rtNormal = TIKI_NEW RenderTarget(engine);
			this->rtNormal->CreateScreenSize();
			this->rtNormal->AddRef();

			this->rtDepth = TIKI_NEW RenderTarget(engine);
			this->rtDepth->CreateScreenSize();
			this->rtDepth->AddRef();

			defaultPostProcess = TIKI_NEW PPDefault(engine, rtBackBuffer);
			defaultPostProcess->AddRef();

			defaultPostProcessPass = defaultPostProcess->GetPasses()[(engine->GetShadowsEnabled() ? 1 : 0)];
			defaultPostProcessPass->AddRef();

#if TIKI_DX10 || TIKI_DX11
#if _DEBUG
			debugLineRenderer = TIKI_NEW DebugLineRenderer(engine);
#endif
#endif

			return true;
		}
		#pragma endregion

		#pragma region Private Member - Dispose - Engine
		void GraphicsModule::disposeEngine()
		{
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

			SafeDelete(&cbufferLights);
			SafeDelete(&cbufferCamera);
			SafeDelete(&cbufferObject);
		}
		#pragma endregion
	}
}