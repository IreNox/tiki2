#pragma once

#include "Core/PostProcess.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class PPScreenSpaceAmbientOcclusion : public PostProcess
		{
		public:

			PPScreenSpaceAmbientOcclusion(Engine* engine);
			~PPScreenSpaceAmbientOcclusion();
			
			void UpdatePass(UInt32 index, const DrawArgs& args);

			IRenderTarget* GetAO();

		private:

			IShader* shader;
			ITexture* randomTexture;
			IRenderTarget* aoTarget;

		};
	}
}