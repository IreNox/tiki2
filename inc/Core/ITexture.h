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

			virtual Int32 GetWidth() = 0;
			virtual Int32 GetHeight() = 0;

		};
	}
}

