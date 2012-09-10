#pragma once

#include "Core/IResource.h"

namespace TikiEngine
{
	namespace Resources
	{
		class ITexture : public IResource
		{
		public:

			ITexture(Engine* engine)
				: IResource(engine)
			{
			}

			virtual ~ITexture()
			{
			}

			virtual void Create(UInt32 width, UInt32 height, bool dynamic) = 0;

			virtual Int32 GetWidth() = 0;
			virtual Int32 GetHeight() = 0;
			virtual Vector2 GetSize() = 0;

			virtual bool GetDynamic() = 0;

			virtual void GetData(Int32 format, void** data) = 0;
			virtual void SetData(Int32 format, void* data, UInt32 dataLength) = 0;

		};
	}
}

