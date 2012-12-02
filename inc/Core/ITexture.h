#pragma once

#include "Core/IResource.h"
#include "Core/Rectangle.h"

namespace TikiEngine
{
	namespace Resources
	{
		enum PixelFormat
		{
			PF_A8R8G8B8,
			PF_R8G8B8A8 = 28,
			PF_R32G32B32A32 = 2
		};

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

			virtual void Create(UInt32 width, UInt32 height, bool dynamic = false, PixelFormat format = PF_R8G8B8A8) = 0;

			virtual Int32 GetWidth() = 0;
			virtual Int32 GetHeight() = 0;
			virtual Vector2 GetSize() = 0;
			virtual Rectangle GetRectangle() = 0;

			virtual bool GetDynamic() = 0;

			virtual void GetData(PixelFormat format, void** data, UInt32* dataLength) = 0;
			virtual void SetData(PixelFormat format, void* data, UInt32 dataLength) = 0;

		};
	}
}

