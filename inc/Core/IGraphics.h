#pragma once

#include "Core/IModule.h"

#include "Core/ViewPort.h"
#include "Core/IRenderTarget.h"

#include "Core/Light.h"
#include "Core/PostProcess.h"

namespace TikiEngine
{
	namespace Modules
	{
		using TikiEngine::Graphics::PostProcess;
		using TikiEngine::Graphics::PostProcessPass;
		using TikiEngine::Resources::IRenderTarget;
		using TikiEngine::Components::Light;

		class IGraphics : public IModule
		{
		public:

			IGraphics(Engine* engine)
				: IModule(engine)
			{
			}
			virtual ~IGraphics() {}

			void Begin() {}
			virtual void Begin(const DrawArgs& args) = 0;
						
			virtual void* GetDevice() = 0;
			virtual void* GetDeviceContext() = 0;

			virtual void AddPostProcess(PostProcess* postProcess) = 0;
			virtual void RemovePostProcess(PostProcess* postProcess) = 0;

			virtual ViewPort* GetViewPort() = 0;
			virtual IRenderTarget* GetScreenBuffer() = 0;

			virtual void SetLightChanged(List<Light*>* lights) = 0;
		};
	}
}

