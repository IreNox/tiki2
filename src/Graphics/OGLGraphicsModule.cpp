
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
			if (ok) ok &= (glewInit() == GLEW_OK);
			if (ok) ok &= initOpenGL();

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
		bool GraphicsModule::initExtensions()
		{
			HDC devContext = GetDC(hWnd);
			HGLRC renContext = 0;

			if (!devContext)
				return false;

			PIXELFORMATDESCRIPTOR pixelFormat;
			ZeroMemory(&pixelFormat, sizeof(PIXELFORMATDESCRIPTOR));
			if (!SetPixelFormat(devContext, 1, &pixelFormat))
				return false;

			renContext = wglCreateContext(devContext);
			if (!renContext)
				return false;

			if (!wglMakeCurrent(devContext, renContext))
				return false;

			if (!initExtensionList())
				return false;

			wglMakeCurrent(0, 0);
			wglDeleteContext(renContext);
			ReleaseDC(hWnd, devContext);

			return true;
		}

		bool GraphicsModule::initExtensionList()
		{
			//DllMain::Info.wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
			//if(!DllMain::Info.wglChoosePixelFormatARB) return false;

			//DllMain::Info.wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
			//if(!DllMain::Info.wglCreateContextAttribsARB) return false;

			//DllMain::Info.wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
			//if(!DllMain::Info.wglSwapIntervalEXT) return false;

			//DllMain::Info.glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
			//if(!DllMain::Info.glAttachShader) return false;

			//DllMain::Info.glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
			//if(!DllMain::Info.glBindBuffer) return false;

			//DllMain::Info.glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
			//if(!DllMain::Info.glBindVertexArray) return false;

			//DllMain::Info.glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
			//if(!DllMain::Info.glBufferData) return false;

			//DllMain::Info.glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
			//if(!DllMain::Info.glCompileShader) return false;

			//DllMain::Info.glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
			//if(!DllMain::Info.glCreateProgram) return false;

			//DllMain::Info.glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
			//if(!DllMain::Info.glCreateShader) return false;

			//DllMain::Info.glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
			//if(!DllMain::Info.glDeleteBuffers) return false;

			//DllMain::Info.glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
			//if(!DllMain::Info.glDeleteProgram) return false;

			//DllMain::Info.glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
			//if(!DllMain::Info.glDeleteShader) return false;

			//DllMain::Info.glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
			//if(!DllMain::Info.glDeleteVertexArrays) return false;

			//DllMain::Info.glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
			//if(!DllMain::Info.glDetachShader) return false;

			//DllMain::Info.glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
			//if(!DllMain::Info.glEnableVertexAttribArray) return false;

			//DllMain::Info.glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
			//if(!DllMain::Info.glGenBuffers) return false;

			//DllMain::Info.glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
			//if(!DllMain::Info.glGenVertexArrays) return false;

			//DllMain::Info.glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
			//if(!DllMain::Info.glGetAttribLocation) return false;

			//DllMain::Info.glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
			//if(!DllMain::Info.glGetProgramInfoLog) return false;

			//DllMain::Info.glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
			//if(!DllMain::Info.glGetProgramiv) return false;

			//DllMain::Info.glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
			//if(!DllMain::Info.glGetShaderInfoLog) return false;

			//DllMain::Info.glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
			//if(!DllMain::Info.glGetShaderiv) return false;

			//DllMain::Info.glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
			//if(!DllMain::Info.glLinkProgram) return false;

			//DllMain::Info.glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
			//if(!DllMain::Info.glShaderSource) return false;

			//DllMain::Info.glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
			//if(!DllMain::Info.glUseProgram) return false;

			//DllMain::Info.glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
			//if(!DllMain::Info.glVertexAttribPointer) return false;

			//DllMain::Info.glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
			//if(!DllMain::Info.glBindAttribLocation) return false;

			//DllMain::Info.glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
			//if(!DllMain::Info.glGetUniformLocation) return false;

			//DllMain::Info.glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
			//if(!DllMain::Info.glActiveTexture) return false;

			//DllMain::Info.glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
			//if(!DllMain::Info.glGenerateMipmap) return false;

			//DllMain::Info.glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
			//if(!DllMain::Info.glDisableVertexAttribArray) return false;

			//DllMain::Info.glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
			//if(!DllMain::Info.glUniform1i) return false;

			//DllMain::Info.glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
			//if(!DllMain::Info.glUniform1f) return false;

			//DllMain::Info.glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
			//if(!DllMain::Info.glUniform2fv) return false;

			//DllMain::Info.glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
			//if(!DllMain::Info.glUniform3fv) return false;

			//DllMain::Info.glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
			//if(!DllMain::Info.glUniform4fv) return false;

			//DllMain::Info.glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
			//if(!DllMain::Info.glUniformMatrix4fv) return false;

			//DllMain::Info.glGetUniformiv = (PFNGLGETUNIFORMIVPROC)wglGetProcAddress("glGetUniformiv");
			//if(!DllMain::Info.glGetUniformiv) return false;

			//DllMain::Info.glGetUniformfv = (PFNGLGETUNIFORMFVPROC)wglGetProcAddress("glGetUniformfv");
			//if(!DllMain::Info.glGetUniformfv) return false;

			return true;
		}

		bool GraphicsModule::initOpenGL()
		{
			deviceContext = GetDC(hWnd);
			if (!deviceContext)
				return false;

			PIXELFORMATDESCRIPTOR pfd;
			ZeroMemory( &pfd, sizeof( pfd ) );
			pfd.nSize = sizeof( pfd );
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
				PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = 24;
			pfd.cDepthBits = 16;
			pfd.iLayerType = PFD_MAIN_PLANE;
			int iFormat = ChoosePixelFormat(deviceContext, &pfd);
			
			if (!SetPixelFormat(deviceContext, iFormat, &pfd))
				return false;
			
			//int attListPF[] = {
			//	// Support for OpenGL rendering.
			//	WGL_SUPPORT_OPENGL_ARB,
			//	TRUE,
			//	// Support for rendering to a window.
			//	WGL_DRAW_TO_WINDOW_ARB,
			//	TRUE,
			//	// Support for hardware acceleration.
			//	WGL_ACCELERATION_ARB,
			//	WGL_FULL_ACCELERATION_ARB,
			//	// Support for 24bit color.
			//	WGL_COLOR_BITS_ARB,
			//	24,
			//	// Support for 24 bit depth buffer.
			//	WGL_DEPTH_BITS_ARB,
			//	24,
			//	// Support for double buffer.
			//	WGL_DOUBLE_BUFFER_ARB,
			//	TRUE,
			//	// Support for swapping front and back buffer.
			//	WGL_SWAP_METHOD_ARB,
			//	WGL_SWAP_EXCHANGE_ARB,
			//	// Support for the RGBA pixel type.
			//	WGL_PIXEL_TYPE_ARB,
			//	WGL_TYPE_RGBA_ARB,
			//	// Support for a 8 bit stencil buffer.
			//	WGL_STENCIL_BITS_ARB,
			//	8,
			//	// Null terminate the attribute list.
			//	0
			//};	

			//int pixelFormat[10];
			//UInt32 formatCount;
			//if (!wglChoosePixelFormatARB(deviceContext, attListPF, 0, 10, pixelFormat, &formatCount))
			//	return false;
			//

			//PIXELFORMATDESCRIPTOR pixelDesc;
			//ZeroMemory(&pixelFormat, sizeof(PIXELFORMATDESCRIPTOR));
			////{
			////	sizeof(PIXELFORMATDESCRIPTOR), // Die größe muss natürlich stimmen
			////	1, // Versionsnummer
			////	PFD_DRAW_TO_WINDOW | 
			////	// Das Format muss in Fenster sichtbar sein können
			////	PFD_SUPPORT_OPENGL | 
			////	// OpenGL muss unterstützt werden
			////	PFD_DOUBLEBUFFER, 
			////	// Double Buffering muss unterstützt werden
			////	PFD_TYPE_RGBA, 
			////	// Das RGBA (Rot,Grün,Blau,Alpha(Transparenz)) 
			////	// muss unterstützt werden
			////	24, 
			////	// Die Farbtiefe, die schon 
			////	// übergeben wurde, wird hier benötigt
			////	0, 0, 0, 0, 0, 0, // wird nicht benötigt
			////	0, // kein Alpha Buffer
			////	0, // Shift Bit ignoriert
			////	0, // kein Accumulation Buffer
			////	0, 0, 0, 0, // nicht benötigt
			////	24, // 16Bit Z-Buffer (Depth Buffer)
			////	0, // kein Stencil Buffer
			////	0, // kein Auxiliary Buffer
			////	PFD_MAIN_PLANE, 
			////	// Die Hauptebene auf die später gezeichnet wird
			////	0, // unwichtig
			////	0, 0, 0 // keine Ebenenmasken benötigt
			////};
			//if (!SetPixelFormat(deviceContext, 1, &pixelDesc))
			//	return false;

			//int attListRC[] = {
			//	// Set the 4.0 version of OpenGL in the attribute list.
			//	WGL_CONTEXT_MAJOR_VERSION_ARB,
			//	4,
			//	WGL_CONTEXT_MINOR_VERSION_ARB,
			//	0,
			//	// Null terminate the attribute list.
			//	0
			//};

			renderContext = wglCreateContext(deviceContext);
			//renderContext = DllMain::Info.wglCreateContextAttribsARB(deviceContext, 0, attListRC);
			if (!renderContext)
				return false;

			if (!wglMakeCurrent(deviceContext, renderContext))
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