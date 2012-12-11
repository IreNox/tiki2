#pragma once

#include "Core/PostProcess.h"
#include "Graphics/RenderTarget.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class PPDefault : public PostProcess
		{
		public:

			PPDefault(Engine* engine, IRenderTarget* backBuffer);
			~PPDefault();

			void UpdatePass(UInt32 index, const DrawArgs& args);

		private:

			IShader* shaderShadow;
			IShader* shaderDefault;

			RenderTarget* shadowTarget;

		};
	}
}