
#pragma comment(lib, "opengl32.lib")

#include "Graphics/OGLGraphicsModule.h"

#include "Core/Camera.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		GraphicsModule::GraphicsModule(Engine* engine)
			: IGraphics(engine), deviceContext(0), renderContext(0), cbufferLights(0), cbufferCamera(0), cbufferObject(0), rtBackBuffer(0),
			  rtLight(0), rtDepth(0), rtNormal(0), rtInterface(0), rtScreenIndex(false), defaultPostProcess(0), defaultPostProcessPass(0),
			  currentArgs(DrawArgs::Empty)
		{
			clearColor = Color::TikiBlue;

			rtScreen[0] = 0;
			rtScreen[1] = 0;
		}

		GraphicsModule::~GraphicsModule()
		{
		}
		#pragma endregion

		#pragma region Init/Dispose
		bool GraphicsModule::Initialize(EngineDescription& desc)
		{
			hWnd = desc.Window.hWnd;

			bool ok = true;
			if (ok) ok &= initOpenGL();
			if (ok) ok &= initEngine(desc);
			if (ok) ok &= initFrameBuffer();

			return ok;
		}

		void GraphicsModule::Dispose()
		{
			if(renderContext)
			{
				wglMakeCurrent(NULL, NULL);
				wglDeleteContext(renderContext);
				renderContext = 0;
			}

			if(deviceContext)
			{
				ReleaseDC(hWnd, deviceContext);
				deviceContext = 0;
			}
		}
		#pragma endregion

		#pragma region Init - Private
		bool GraphicsModule::initOpenGL()
		{
			deviceContext = GetDC(hWnd);
			if (!deviceContext)
				return false;

			PIXELFORMATDESCRIPTOR pixelDesc;
			ZeroMemory(&pixelDesc, sizeof(pixelDesc));
			pixelDesc.nSize = sizeof(pixelDesc);
			pixelDesc.nVersion = 1;
			pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pixelDesc.iPixelType = PFD_TYPE_RGBA;
			pixelDesc.cColorBits = 32;
			pixelDesc.cDepthBits = 24;
			pixelDesc.cStencilBits = 8;
			pixelDesc.cAlphaBits = 8;
			pixelDesc.iLayerType = PFD_MAIN_PLANE;
			int pixelFormat = ChoosePixelFormat(deviceContext, &pixelDesc);
			
			if (!SetPixelFormat(deviceContext, pixelFormat, &pixelDesc))
				return false;
			
			renderContext = wglCreateContext(deviceContext);
			if (!renderContext)
				return false;

			if (!wglMakeCurrent(deviceContext, renderContext))
				return false;

			// Extensions
			if (glewInit() != GLEW_OK)
				return false;

			if (!GL_VERSION_4_3)
				return false;

			// Depth Buffer
			glClearDepth(1.0f);
			glDepthFunc(GL_LEQUAL);	
			glEnable(GL_DEPTH_TEST);

			// Back face culling
			glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			glClearColor(clearColor.R, clearColor.G, clearColor.B, clearColor.A);

			RECT rect;
			GetClientRect(hWnd, &rect);
			viewPort = ViewPort(0, 0, rect.right, rect.bottom, 0.001f, 1000.0f);

			glViewport(0, 0, viewPort.Width, viewPort.Height);
			
			return true;
		}

		bool GraphicsModule::initFrameBuffer()
		{
			glGenFramebuffers(1, &frameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

			rtScreen[0]->Apply(0);

			UInt32 depth = 0;
			glGenRenderbuffers(1, &depth);
			glBindRenderbuffer(GL_TEXTURE_2D, depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, viewPort.Width, viewPort.Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			//UInt32 stencil = 0;
			//glGenRenderbuffers(1, &stencil);
			//glBindRenderbuffer(GL_TEXTURE_2D, stencil);
			//glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, viewPort.Width, viewPort.Height);
			//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, stencil);

			switch (glCheckFramebufferStatus(GL_FRAMEBUFFER))
			{
			case GL_FRAMEBUFFER_COMPLETE:
				break;

			case GL_FRAMEBUFFER_UNSUPPORTED:
				throw string("FBO Building failed! Unsupported framebuffer format.");

			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				throw string("FBO Building failed! Missing attachment.");

			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				throw string("FBO Building failed! Attachment type error.");

			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				throw string("FBO Building failed! Missing draw buffer.");

			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				throw string("FBO Building failed! Missing read buffer.");

			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				throw string("FBO Building failed! Attached images must have the same number of samples.");

			default:
				throw string("FBO Building failed! Fatal error.");
			}

			//if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			//	return false;

			return true;
		}
		#pragma endregion

		#pragma region Member - Begin/End
		void GraphicsModule::Begin(DrawArgs& args)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

			CBMatrices* mat = cbufferCamera->MapTI();
			*mat = args.CurrentCamera->GetMatrices();
			cbufferCamera->Unmap();
			
			rtInterface->Clear(Color::TransparentBlack);
			rtScreen[rtScreenIndex]->Apply(0);
			rtScreen[rtScreenIndex]->Clear(clearColor);

			rtDepth->Clear(Color::Black);
			rtDepth->Apply(1);
			rtNormal->Clear(Color::Black);
			rtNormal->Apply(2);
			rtLight->Clear(Color::TransparentBlack);
			rtLight->Apply(3);

			glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}

		void GraphicsModule::End()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			SwapBuffers(deviceContext);
		}
		#pragma endregion

		#pragma region Member - RenderTarget
		void GraphicsModule::SwitchScreenTarget(IRenderTarget** inputTarget, IRenderTarget** outputTarget)
		{

		}

		void GraphicsModule::SetRenderTarget(UInt32 slot, UInt32 target)
		{
			while (slot >= renderTargets.Count())
			{
				renderTargets.Add(0);
			}

			if (renderTargets[slot] == target) return;

			renderTargets[slot] = target;
			if (target)
				glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, target, 0);

			//static const GLenum attachments[] = {
			//	GL_COLOR_ATTACHMENT0,
			//	GL_COLOR_ATTACHMENT1,
			//	GL_COLOR_ATTACHMENT2,
			//	GL_COLOR_ATTACHMENT3,
			//	GL_COLOR_ATTACHMENT4,
			//	GL_COLOR_ATTACHMENT5,
			//	GL_COLOR_ATTACHMENT6,
			//	GL_COLOR_ATTACHMENT7,
			//	GL_COLOR_ATTACHMENT8,
			//	GL_COLOR_ATTACHMENT9,
			//	GL_COLOR_ATTACHMENT10,
			//	GL_COLOR_ATTACHMENT11,
			//	GL_COLOR_ATTACHMENT12,
			//	GL_COLOR_ATTACHMENT13,
			//	GL_COLOR_ATTACHMENT14,
			//	GL_COLOR_ATTACHMENT15
			//};

			//glDrawBuffers(
			//	renderTargets.Count(),
			//	attachments
			//);

			if (!target)
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void GraphicsModule::SetFirstAndOnlyRenderTargets(UInt32 target)
		{
			renderTargets.Clear();
			this->SetRenderTarget(0, target);
		}
		#pragma endregion

		#pragma region Member - Set
		void GraphicsModule::SetCulling(bool value)
		{
			(value ? glEnable : glDisable)(GL_CULL_FACE);
		}

		void GraphicsModule::SetStateAlphaBlend(BlendStateModes value)
		{			
			switch (value)
			{
			case BSM_Disable:
				glDisable(GL_BLEND);
				break;
			case BSM_Interface:
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				//glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
				//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
				break;
			case BSM_Particles:
				glEnable(GL_BLEND);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
				glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				break;
			}
		}

		void GraphicsModule::SetStateDepthEnabled(bool value)
		{
			(value ? glEnable : glDisable)(GL_DEPTH_TEST);
		}
		#pragma endregion

		#pragma region Member - Misc
		void GraphicsModule::Reset()
		{
			viewPort.Width = engine->GetEngineDescription().Graphics.Width;
			viewPort.Height = engine->GetEngineDescription().Graphics.Height;

			glViewport(0, 0, viewPort.Width, viewPort.Height);
		}

		void GraphicsModule::MakeScreenshot(wcstring fileName)
		{

		}
		#pragma endregion

		#pragma region Member - Debug
		void GraphicsModule::DrawLine(const Vector3& start, const Vector3& end, const Color& color)
		{

		}

		void GraphicsModule::DrawLine(List<Vector3>* points, const Color& color, bool lastToFirst)
		{

		}
		#pragma endregion	
	}
}