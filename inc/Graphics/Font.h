#pragma once

#include "Core/IFont.h"

#include "Core/RectangleF.h"
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

			float DrawChar(wchar_t c, const Vector2& pos, const Color& color, float layerDepth);

			float GetHeight();
			bool ContainsChar(wchar_t cChar);
			Vector2 MeasureString(wstring text);

			ITexture* GetTexture();
			void* GetNativeResource();

			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

			float pixelHeight;
			Dictionary<wchar_t, RectangleF> charRect;

			ITexture* texture;

			void createGdiImage(void* font, DWORD** pixels, int* width, int* height);
			void fillTexture(DWORD* pixels, int width, int height);

		};
	}
}