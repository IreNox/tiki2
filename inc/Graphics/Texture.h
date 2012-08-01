#pragma once

#include "Core/TypeInc.h"

#include <d3d11.h>
#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace Resources
	{
		using TikiEngine::IO::Stream;

		class Texture : public ITexture
		{
		public:

			Texture(Engine* engine);
			~Texture();

			Int32 GetWidth();
			Int32 GetHeight();

			void GetData(Int32 format, void** data);
			void SetData(Int32 format, void* data, UInt32 dataLength);

			void* GetNativeResource();

			bool GetReady();

		protected:

			void loadFromStream(Stream* stream);
			void saveToStream(Stream* stream);

		private:

			ID3D11Texture2D* texture;
			ID3D11ShaderResourceView* textureResource;

			D3D11_TEXTURE2D_DESC desc;

		};
	}
}
