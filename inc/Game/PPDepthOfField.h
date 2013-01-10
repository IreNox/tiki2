#pragma once

#include "Core/PostProcess.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class PPDepthOfField : public PostProcess
		{
		public:

			PPDepthOfField(Engine* engine);
			~PPDepthOfField();

			void UpdatePass(UInt32 index, const DrawArgs& args);

		private:

			IShader* shader;
			IRenderTarget* verticleTarget;

		};
	}
}