#pragma once

#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace Graphics
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


		};
	}
}
