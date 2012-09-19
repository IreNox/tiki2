#pragma once

#include "Core/IFont.h"

#include "Core/Rectangle.h"
#include "Core/Dictionary.h"

namespace TikiEngine
{
	namespace Resources
	{
		class Font : public IFont
		{
		public:

			Font(Engine* engine);
			~Font();

			void Create(wcstring fontName, float fontSize);

			float DrawChar(wchar_t c, const Vector2& pos);

			UInt32 GetHeight();
			ITexture* GetTexture();
			void* GetNativeResource();

			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

			UInt32 pixelHeight;
			Dictionary<wchar_t, Rectangle> charRect;

			ITexture* texture;

			void createGdiImage(wcstring fontName, float fontSize, DWORD** pixels, int* width, int* height);
			void fillTexture(DWORD* pixels, int width, int height);

		};
	}
}