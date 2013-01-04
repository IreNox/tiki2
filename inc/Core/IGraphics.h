#pragma once

#include "Core/IModule.h"

#include "Core/ViewPort.h"
#include "Core/IRenderTarget.h"
#include "Core/IConstantBuffer.h"

#include "Core/Light.h"
#include "Core/PostProcess.h"

#include "Core/EventScreenSizeChanged.h"

namespace TikiEngine
{
	namespace Modules
	{
		using TikiEngine::Graphics::PostProcess;
		using TikiEngine::Graphics::PostProcessPass;
		using TikiEngine::Graphics::IConstantBuffer;
		using TikiEngine::Resources::ITexture;
		using TikiEngine::Resources::IRenderTarget;
		using TikiEngine::Components::Light;

        enum BlendStateModes
        {
            BSM_Interface,
            BSM_Particles,
            BSM_Disable
        };

		class IGraphics : public IModule
		{
		public:

			ScreenSizeChangedEvent ScreenSizeChanged;

			IGraphics(Engine* engine)
				: IModule(engine)
			{
			}
			virtual ~IGraphics() {}

			void Begin() { throw "Not supported"; }
			virtual void Begin(DrawArgs& args) = 0;
			
#if _DEBUG
			virtual void DrawLine(const Vector3& start, const Vector3& end, const Color& color) = 0;
			virtual void DrawLine(List<Vector3>* points, const Color& color, bool lastToFirst = false) = 0;

			virtual void DrawConsole(const DrawArgs& args) = 0;
#endif

			virtual void* GetDevice() = 0;
			virtual void* GetDeviceContext() = 0;

			virtual void AddPostProcess(PostProcess* postProcess) = 0;
			virtual void RemovePostProcess(PostProcess* postProcess) = 0;

			virtual void AddDefaultProcessTarget(cstring varName, IRenderTarget* target) = 0;
			virtual void SwitchScreenTarget(IRenderTarget** inputTarget, IRenderTarget** outputTarget) = 0;

			virtual ViewPort* GetViewPort() = 0;

			virtual IRenderTarget* GetDepthTarget() = 0;
			virtual IRenderTarget* GetLightTarget() = 0;
			virtual IRenderTarget* GetNormalTarget() = 0;
			virtual IRenderTarget* GetScreenTarget() = 0;
			virtual IRenderTarget* GetUnusedScreenTarget() = 0;
			virtual IRenderTarget* GetInterfaceTarget() = 0;

			virtual void SetCulling(bool value) = 0;
			virtual void SetStateAlphaBlend(BlendStateModes value) = 0;
			virtual void SetStateDepthEnabled(bool value) = 0;

			virtual IConstantBuffer* CreateConstantBuffer(UInt32 size) = 0;

			/*! @brief Reset the Graphics Device and apply new values. Use values from Engine::GetDescription() */
			virtual void Reset() = 0;

			/*!
			 * @brief Save an Screen shot image from the last Frame on HDD 
			 * @param fileName Filename for Screen shot. Use NULL for default Name.
			 */
			virtual void MakeScreenshot(wcstring fileName = 0) = 0;

		};
	}
}

