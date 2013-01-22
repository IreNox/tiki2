#pragma once

#include "Core/TypeInc.h"
#include "Core/ITexture.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Resources
	{
		using TikiEngine::IO::Stream;

		class Texture : public ITexture
		{
			friend class RenderTarget;

		public:

			Texture(Engine* engine);
			Texture(Engine* engine, TDX_Texture2D* tex, bool createShaderView, bool dynamic);
			~Texture();

			void Create(UInt32 width, UInt32 height, bool dynamic, PixelFormat format);

			Int32 GetWidth();
			Int32 GetHeight();
			Vector2 GetSize();
			Vector2 GetCenter();
			Rectangle GetRectangle();

			void GetData(PixelFormat format, void** data, UInt32* dataLength);
			void SetData(PixelFormat format, void* data, UInt32 dataLength);

			bool GetDynamic();
			void* GetNativeResource();

			bool GetReady();

		protected:

			void createInternal(UInt32 width, UInt32 height, bool dynamic, PixelFormat format);

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

			bool dynamic;

			TDX_Texture2D* texture;
			TDX_ShaderResourceView* textureResource;

			TDX_Texture2D_Desc desc;

		};
	}
}
