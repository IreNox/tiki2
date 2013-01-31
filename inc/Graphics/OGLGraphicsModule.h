#pragma once

#include "Core/IGraphics.h"

#include "Core/CBMatrices.h"
#include "Graphics/CBLights.h"
#include "Graphics/CBObjectData.h"

#include "Graphics/Quad.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/ConstantBuffer.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Graphics;

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
#endif

			void* GetDevice() { return deviceContext; }
			void* GetDeviceContext() { return renderContext; }
			ViewPort* GetViewPort() { return &viewPort; }

			IRenderTarget* GetDepthTarget() { return rtDepth; }
			IRenderTarget* GetLightTarget() { return rtLight; }
			IRenderTarget* GetNormalTarget() { return rtNormal; }
			IRenderTarget* GetScreenTarget() { return rtScreen[rtScreenIndex]; }
			IRenderTarget* GetUnusedScreenTarget() { return rtScreen[!rtScreenIndex]; }
			IRenderTarget* GetInterfaceTarget() { return rtInterface; }

			ConstantBuffer<CBLights>* GetCBufferLight();
			ConstantBuffer<CBMatrices>* GetCBufferCamera();
			ConstantBuffer<CBObjectData>* GetCBufferObject();

			void AddPostProcess(PostProcess* postProcess);
			void RemovePostProcess(PostProcess* postProcess);

			void AddScreenSizeRenderTarget(RenderTarget* target);
			void RemoveScreenSizeRenderTarget(RenderTarget* target);

			void AddDefaultProcessTarget(cstring varName, IRenderTarget* target);
			void SwitchScreenTarget(IRenderTarget** inputTarget, IRenderTarget** outputTarget);

			void SetRenderTarget(UInt32 slot, UInt32 target);
			void SetFirstAndOnlyRenderTargets(UInt32 target);

			void SetCulling(bool value);
			void SetStateAlphaBlend(BlendStateModes value);
			void SetStateDepthEnabled(bool value);

			IConstantBuffer* CreateConstantBuffer(UInt32 size);
			
			void Reset();
			void MakeScreenshot(wcstring fileName);

		private:
			
			DrawArgs& currentArgs;

			HWND hWnd;
			HDC deviceContext;
			HGLRC renderContext;

			Color clearColor;
			ViewPort viewPort;

			ConstantBuffer<CBLights>* cbufferLights;
			ConstantBuffer<CBMatrices>* cbufferCamera;
			ConstantBuffer<CBObjectData>* cbufferObject;

			RenderTarget* rtBackBuffer;
			RenderTarget* rtLight;
			RenderTarget* rtDepth;
			RenderTarget* rtNormal;
			RenderTarget* rtInterface;
			RenderTarget* rtScreen[2];
			bool rtScreenIndex;

			UInt32 frameBuffer;
			UInt32 depthBuffer;
			List<UInt32> renderTargets;

			List<RenderTarget*> screenSizeRenderTargets;

			PostProcess* defaultPostProcess;
			PostProcessPass* defaultPostProcessPass;
			List<PostProcess*> postProcesses;
			Dictionary<PostProcessPass*, Quad*> postProcessPassQuads;

			bool initOpenGL();
			bool initFrameBuffer();

			bool initEngine(EngineDescription& desc);
			void disposeEngine();

			void drawPostProcess(PostProcess* postProcess);
			void setLightChanged(const DrawArgs& args);

		};
	}
}