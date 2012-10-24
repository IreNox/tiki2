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
			Texture(Engine* engine, ID3D11Texture2D* tex, bool createShaderView, bool dynamic);
			~Texture();

			void Create(UInt32 width, UInt32 height, bool dynamic);

			Int32 GetWidth();
			Int32 GetHeight();
			Vector2 GetSize();
			Rectangle GetRectangle();

			void GetData(Int32 format, void** data);
			void SetData(Int32 format, void* data, UInt32 dataLength);

			bool GetDynamic();
			void* GetNativeResource();

			bool GetReady();

		protected:

			void createInternal(UInt32 width, UInt32 height, bool dynamic);

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

			bool dynamic;

			ID3D11Texture2D* texture;
			ID3D11ShaderResourceView* textureResource;

			D3D11_TEXTURE2D_DESC desc;

		};
	}
}
