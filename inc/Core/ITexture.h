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

			virtual void LoadFromFile(wstring fileName) = 0;
			virtual void Create(Int32 width, Int32 height) = 0;

			virtual Int32 GetWidth() = 0;
			virtual Int32 GetHeight() = 0;

			virtual void GetData(Int32 format, void** data) = 0;
			virtual void SetData(Int32 format, void* data, UInt32 dataLength) = 0;

			virtual void* GetResource() = 0;

			virtual bool GetReady() = 0;
		};
	}
}

