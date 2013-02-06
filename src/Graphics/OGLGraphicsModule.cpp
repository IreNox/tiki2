
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
			disposeEngine();

			if (depthBuffer)
			{
				glDeleteRenderbuffers(1, &depthBuffer);
			}

			if (frameBuffer)
			{
				glDeleteFramebuffers(1, &frameBuffer);
			}

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
			glDisable(GL_ALPHA_TEST);

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

			glGenRenderbuffers(1, &depthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, viewPort.Width, viewPort.Height);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
			
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				return false;

			return true;
		}
		#pragma endregion

		#pragma region Member - RenderTarget
		void GraphicsModule::SetRenderTarget(UInt32 slot, UInt32 target)
		{
			while (slot >= renderTargets.Count())
			{
				renderTargets.Add(0);
			}

			if (renderTargets[slot] == target) return;

			renderTargets[slot] = target;
			if (target)
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, target, 0);

				static const GLenum attachments[] = {
					GL_COLOR_ATTACHMENT0,
					GL_COLOR_ATTACHMENT1,
					GL_COLOR_ATTACHMENT2,
					GL_COLOR_ATTACHMENT3,
					GL_COLOR_ATTACHMENT4,
					GL_COLOR_ATTACHMENT5,
					GL_COLOR_ATTACHMENT6,
					GL_COLOR_ATTACHMENT7,
					GL_COLOR_ATTACHMENT8,
					GL_COLOR_ATTACHMENT9,
					GL_COLOR_ATTACHMENT10,
					GL_COLOR_ATTACHMENT11,
					GL_COLOR_ATTACHMENT12,
					GL_COLOR_ATTACHMENT13,
					GL_COLOR_ATTACHMENT14,
					GL_COLOR_ATTACHMENT15
				};

				glDrawBuffers(
					renderTargets.Count(),
					attachments
				);
			}
			else
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glDrawBuffer(GL_COLOR_ATTACHMENT0);
			}
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
#if _DEBUG
		void GraphicsModule::DrawLine(const Vector3& start, const Vector3& end, const Color& color)
		{

		}

		void GraphicsModule::DrawLine(List<Vector3>* points, const Color& color, bool lastToFirst)
		{

		}
#endif
		#pragma endregion	
	}
}