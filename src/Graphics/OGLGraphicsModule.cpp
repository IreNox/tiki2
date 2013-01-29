
#pragma comment(lib, "opengl32.lib")

#include "Graphics/OGLGraphicsModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		#pragma region Class
		GraphicsModule::GraphicsModule(Engine* engine)
			: IGraphics(engine), deviceContext(0), renderContext(0)
		{
			clearColor = Color::TikiBlue;
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

			RECT rect;
			GetClientRect(hWnd, &rect);
			viewPort = ViewPort(0, 0, rect.right, rect.bottom, 0.001f, 1000.0f);

			glViewport(0, 0, viewPort.Width, viewPort.Height);
			
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
			pixelDesc.cColorBits = 24;
			pixelDesc.cDepthBits = 24;
			pixelDesc.cStencilBits = 8;
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
			glEnable(GL_DEPTH_TEST);

			// Back face culling
			glFrontFace(GL_CW);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			return true;
		}
		#pragma endregion

		#pragma region Member - PostProcess
		void GraphicsModule::AddPostProcess(PostProcess* postProcess)
		{

		}

		void GraphicsModule::RemovePostProcess(PostProcess* postProcess)
		{

		}
		#pragma endregion

		#pragma region RenderTarget
		void GraphicsModule::AddDefaultProcessTarget(cstring varName, IRenderTarget* target)
		{

		}

		void GraphicsModule::SwitchScreenTarget(IRenderTarget** inputTarget, IRenderTarget** outputTarget)
		{

		}
		#pragma endregion

		#pragma region Member - Set
		void GraphicsModule::SetCulling(bool value)
		{

		}

		void GraphicsModule::SetStateAlphaBlend(BlendStateModes value)
		{

		}

		void GraphicsModule::SetStateDepthEnabled(bool value)
		{

		}
		#pragma endregion

		#pragma region Member - Misc
		IConstantBuffer* GraphicsModule::CreateConstantBuffer(UInt32 size)
		{
			return 0;
		}

		void GraphicsModule::Reset()
		{

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

		void GraphicsModule::DrawConsole(const DrawArgs& args)
		{

		}
		#pragma endregion

		#pragma region Begin/End
		void GraphicsModule::Begin(DrawArgs& args)
		{
			glClearColor(clearColor.R, clearColor.G, clearColor.B, clearColor.A);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void GraphicsModule::End()
		{
			SwapBuffers(deviceContext);
		}
		#pragma endregion
	}
}