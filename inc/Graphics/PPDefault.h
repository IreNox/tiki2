#pragma once

#include "Core/PostProcess.h"
#include "Core/EventScreenSizeChanged.h"

#include "Graphics/RenderTarget.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class PPDefault : public PostProcess, public ScreenSizeChangedEventHandler
		{
		public:

			PPDefault(Engine* engine, IRenderTarget* backBuffer);
			~PPDefault();

			void UpdatePass(UInt32 index, const DrawArgs& args);

			void Handle(IGraphics* sender, const ScreenSizeChangedArgs& args);

		private:

			IShader* shaderShadow;
			IShader* shaderDefault;

			RenderTarget* shadowTarget;

		};
	}
}