#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class ITexture : public EngineObject
		{
		public:

			ITexture(Engine* engine)
				: EngineObject(engine)
			{
			}

			virtual ~ITexture()
			{
			}


		};
	}
}

