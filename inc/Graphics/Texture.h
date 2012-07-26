#pragma once

#include "Core/TypeInc.h"

#include <d3d11.h>
#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class Texture : public ITexture
		{
		public:

			Texture(Engine* engine);
			~Texture();

			void LoadFromFile(wstring fileName);
			void Create(Int32 width, Int32 height);

			Int32 GetWidth();
			Int32 GetHeight();

			void GetData(Int32 format, void** data);
			void SetData(Int32 format, void* data, UInt32 dataLength);

			void* GetResource();

			bool GetReady();

		private:

			ID3D11ShaderResourceView* texture;
		};
	}
}
