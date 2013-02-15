
#pragma comment(lib, "gdiplus.lib")

#include <Windows.h>

#include "Core/TypeGlobals.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"
#include "Core/NotSupportedException.h"

#include "Graphics/Font.h"
#include "Graphics/DllMain.h"
#include "Graphics/Texture.h"
#include "Graphics/SpriteBatchModule.h"

#include <GdiPlus.h>
using namespace Gdiplus;

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Font::Font(Engine* engine)
			: IFont(engine), texture(0), pixelHeight(0)
		{
		}

		Font::~Font()
		{
			SafeRelease(&texture);
		}
		#pragma endregion

		#pragma region Member - Create
		void Font::Create(wcstring fontName, float fontSize)
		{
			int width = 0;
			int height = 0;
			DWORD* pixels;
			
			ULONG_PTR           gdiplusToken;  
			GdiplusStartupInput gdiplusStartupInput;
			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

			//Gdiplus::Font* font = new Gdiplus::Font(fontName, fontSize);

			Gdiplus::PrivateFontCollection* fontCollection = new Gdiplus::PrivateFontCollection();

			wstring filePath = engine->librarys->GetResourcePath(typeid(IFont).hash_code(), fontName);
			Stream* stream = engine->content->LoadData(filePath);

			Byte* data = new Byte[stream->GetLength()];
			stream->Read(data, 0, stream->GetLength());
			fontCollection->AddMemoryFont(data, (int)stream->GetLength());

			{
				int found = 0;
				FontFamily family;
				fontCollection->GetFamilies(1, &family, &found);

				Gdiplus::Font* font = new Gdiplus::Font(&family, fontSize, FontStyleRegular, UnitPixel);

				this->createGdiImage(font, &pixels, &width, &height);
				this->fillTexture(pixels, width, height);
			}
			
			delete[](data);
			delete(stream);
			delete(fontCollection);
			GdiplusShutdown(gdiplusToken);
			delete[](pixels);
		}
		#pragma endregion

		#pragma region Member
		bool Font::ContainsChar(wchar_t cChar)
		{
			return charRect.ContainsKey(cChar);
		}

		Vector2 Font::MeasureString(wstring text)
		{
			UInt32 i = 0;
			float width = 0.0f;
			RectangleF rect;

			while (i < text.Length())
			{
				wchar_t c = text[i];

				if (charRect.TryGetValue(c, &rect))
				{
					width += rect.Width;
				}
				else
				{
					throw "Char not in Font.";
				}

				i++;
			}

			return Vector2(
				width,
				(float)pixelHeight
			);
		}

		float Font::GetHeight()
		{
			return pixelHeight;
		}

		ITexture* Font::GetTexture()
		{
			return texture;
		}

		void* Font::GetNativeResource()
		{
			return texture;
		}

		bool Font::GetReady()
		{
			return (texture != 0);
		}
		#pragma endregion

		#pragma region Member - Draw
		float Font::DrawChar(wchar_t c, const Vector2& pos, const ::Color& color, float layerDepth)
		{
			RectangleF r;

			if (charRect.TryGetValue(c, &r))
			{
				DllMain::ModuleSpriteBatch->Draw(
					texture,
					RectangleF::Create(
						pos.X,
						pos.Y,
						r.Width,
						r.Height
					),
					r,
					color,
					layerDepth
				);
			}

			return (float)r.Width;
		}
		#pragma endregion

		#pragma region Protected Member - Load/Save
		void Font::loadFromStream(wcstring fileName, Stream* stream)
		{
			int width = 0;
			int height = 0;
			DWORD* pixels;

			ULONG_PTR           gdiplusToken;  
			GdiplusStartupInput gdiplusStartupInput;
			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

			Gdiplus::PrivateFontCollection fontCollection;

			Byte* data = new Byte[stream->GetLength()];
			stream->Read(data, 0, stream->GetLength());
			fontCollection.AddMemoryFont(data, (int)stream->GetLength());

			int found = 0;
			FontFamily family;
			fontCollection.GetFamilies(1, &family, &found);

			Gdiplus::Font font(&family, 14.0f, FontStyleRegular, UnitPixel);

			this->createGdiImage(&font, &pixels, &width, &height);
			this->fillTexture(pixels, width, height);

			GdiplusShutdown(gdiplusToken);
			delete[](pixels);
		}

		void Font::saveToStream(wcstring fileName, Stream* stream)
		{
			throw NotSupportedException();
		}
		#pragma endregion

		#pragma region Private Member
		void Font::createGdiImage(void* fontIn, DWORD** pixels, int* width, int* height)
		{
			Gdiplus::Font* font = (Gdiplus::Font*)fontIn;

			wcstring chars = L" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzäöü0123456789!\"§$%&/()=?,.-;:_#'+*~<>|";
			PInt len = wcslen(chars);
			
			pixelHeight = font->GetHeight(96);

			*width = 512;
			*height = 512;
			int size = *width * *height;
			int stride = 4 * *width;

			*pixels = new DWORD[size];
			ZeroMemory(*pixels, sizeof(DWORD) * size);

			Bitmap bmp(*width, *height, stride, PixelFormat32bppARGB, (BYTE*)*pixels);
			Gdiplus::Graphics* g = Gdiplus::Graphics::FromImage(&bmp);

			SolidBrush bg(Gdiplus::Color(255, 255, 0, 0));
			SolidBrush black(Gdiplus::Color::Black);
			
			g->FillRectangle(
				&bg,
				0,
				0,
				*width,
				*height
			);

			StringFormat format(StringFormatFlagsNoFitBlackBox);

			PInt i = 0;
			float spaceWidth = 0;
			PointF pos = PointF(0, 0);
			RectF charSize = RectF(0, 0, 0, 0);
			while (i < len)
			{
				g->MeasureString(
					chars + i,
					1,
					font,
					pos,
					&format,
					&charSize
				);

				if (pos.X + charSize.Width > *width)
				{
					pos.X = 0;
					pos.Y += pixelHeight;
				}

				g->DrawString(
					chars + i,
					1,
					font,
					pos,
					&black
				);
				
				if (i == 0)
				{
					spaceWidth = charSize.Width / 2;
				}

				charRect.Add(
					chars[i],
					RectangleF::Create(
						pos.X + 2,
						pos.Y,
						(charSize.Width - spaceWidth),
						pixelHeight
					)
				);

				pos.X += charSize.Width;
				i++;
			}

			delete(g);
		}

		void Font::fillTexture(DWORD* pixels, int width, int height)
		{
			UInt32 i = 0;
			UInt32 size = width * height;
			while (i < size)
			{
				pixels[i] = ~(pixels[i] << 8);
				i++;
			}

			texture = TIKI_NEW Texture(engine);
			texture->Create(512, 512, true);
			texture->SetData(
				PF_A8R8G8B8,
				pixels,
				sizeof(DWORD) * width * height
			);

			charRect.Optimize();
		}
		#pragma endregion
	}
}
