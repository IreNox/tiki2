#pragma once

#include "Core/Resource.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using TikiEngine::Resources::Resource;

		class ITexture : public Resource
		{
		public:

			ITexture(Engine* engine)
				: Resource(engine)
			{
			}

			virtual ~ITexture()
			{
			}

			virtual Int32 GetWidth() = 0;
			virtual Int32 GetHeight() = 0;

			virtual void GetData(Int32 format, void** data) = 0;
			virtual void SetData(Int32 format, void* data, UInt32 dataLength) = 0;

		};
	}
}

