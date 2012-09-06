#pragma once

#include "Core/PostProcess.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class PPBlur : public PostProcess
		{
		public:

			PPBlur(Engine* engine);
			~PPBlur();

			void UpdatePass(UInt32 index, const GameTime& time);
			
		private:

			IShader* shader;
			IRenderTarget* verticleTarget;

		};
	}
}