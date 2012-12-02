#pragma once

#include "Core/Color.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace Resources
	{
		class IRenderTarget : public ITexture
		{
		public:

			IRenderTarget(Engine* engine)
				: ITexture(engine)
			{
			}

			virtual ~IRenderTarget()
			{
			}

			virtual void CreateScreenSize(bool dynamic = false, PixelFormat format = PF_R32G32B32A32) = 0;

			virtual void Apply(UInt32 slot) = 0;
			virtual void ApplyFirstAndOnly() = 0;

			virtual void Clear(const Color& color) = 0;
			
		};
	}
}
