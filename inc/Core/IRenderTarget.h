#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class IRenderTarget : public EngineObject
		{
		public:

			IRenderTarget(Engine* engine)
				: EngineObject(engine)
			{
			}

			virtual ~IRenderTarget()
			{
			}


		};
	}
}
