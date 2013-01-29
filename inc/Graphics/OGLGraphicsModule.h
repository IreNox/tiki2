#pragma once

#include "Core/IGraphics.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Modules
	{
		class GraphicsModule : public IGraphics
		{
		public:

			GraphicsModule(Engine* engine);
			~GraphicsModule();

			bool Initialize(EngineDescription& desc);
			void Dispose();

			void Begin(DrawArgs& args);
			void End();

#if _DEBUG
			void DrawLine(const Vector3& start, const Vector3& end, const Color& color);
			void DrawLine(List<Vector3>* points, const Color& color, bool lastToFirst = false);

			void DrawConsole(const DrawArgs& args);
#endif

			void* GetDevice() { return deviceContext; }
			void* GetDeviceContext() { return renderContext; }
			ViewPort* GetViewPort() { return &viewPort; }

			IRenderTarget* GetDepthTarget() { return 0; }
			IRenderTarget* GetLightTarget() { return 0; }
			IRenderTarget* GetNormalTarget() { return 0; }
			IRenderTarget* GetScreenTarget() { return 0; }
			IRenderTarget* GetUnusedScreenTarget() { return 0; }
			IRenderTarget* GetInterfaceTarget() { return 0; }

			IConstantBuffer* GetCBufferObject() { return 0; }

			void AddPostProcess(PostProcess* postProcess);
			void RemovePostProcess(PostProcess* postProcess);

			void AddDefaultProcessTarget(cstring varName, IRenderTarget* target);
			void SwitchScreenTarget(IRenderTarget** inputTarget, IRenderTarget** outputTarget);

			void SetCulling(bool value);
			void SetStateAlphaBlend(BlendStateModes value);
			void SetStateDepthEnabled(bool value);

			IConstantBuffer* CreateConstantBuffer(UInt32 size);
			
			void Reset();
			void MakeScreenshot(wcstring fileName);

		private:
			
			HWND hWnd;
			HDC deviceContext;
			HGLRC renderContext;

			Color clearColor;

			ViewPort viewPort;

			bool initExtensions();
			bool initOpenGL();

		};
	}
}