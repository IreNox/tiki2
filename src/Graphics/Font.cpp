
#include <Windows.h>

#include "Graphics/Font.h"
#include "Core/TypeGlobals.h"

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
			
			this->createGdiImage(fontName, fontSize, &pixels, &width, &height);
			this->fillTexture(pixels, width, height);
		}
		#pragma endregion

		#pragma region Member
		UInt32 Font::GetHeight()
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
		float Font::DrawChar(wchar_t c, const Vector2& pos)
		{
			Rectangle r;

			if (charRect.ContainsKey(c))
			{
				r = charRect[c];

				DllMain::ModuleSpriteBatch->Draw(
					texture,
					Rectangle(
						(int)pos.Y,
						(int)pos.Y,
						(int)r.Width,
						(int)r.Height
					),
					r
				);
			}

			return (float)r.Width;
		}
		#pragma endregion

		#pragma region Protected Member - Load/Save
		void Font::loadFromStream(wcstring fileName, Stream* stream)
		{

		}

		void Font::saveToStream(wcstring fileName, Stream* stream)
		{

		}
		#pragma endregion

		#pragma region Private Member
		void Font::createGdiImage(wcstring fontName, float fontSize, DWORD** pixels, int* width, int* height)
		{
			ULONG_PTR           gdiplusToken;  
			GdiplusStartupInput gdiplusStartupInput;
			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

			wcstring chars = L" ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"§$%&/()=?,.-;:_#'+*~<>|";
			PInt len = wcslen(chars);

			Gdiplus::Font* font = new Gdiplus::Font(fontName, fontSize);
			pixelHeight = (UInt32)ceil(font->GetHeight(96));

			*width = 512;
			*height = 512;
			int size = *width * *height;
			int stride = 4 * *width;

			*pixels = new DWORD[size];
			ZeroMemory(*pixels, sizeof(DWORD) * size);

			Bitmap* bmp = new Bitmap(*width, *height, stride, PixelFormat32bppARGB, (BYTE*)*pixels);
			Gdiplus::Graphics* g = Gdiplus::Graphics::FromImage(bmp);

			SolidBrush* bg = new SolidBrush(Gdiplus::Color(255, 255, 0, 0));
			SolidBrush* black = new SolidBrush(Gdiplus::Color::Black);
			
			g->FillRectangle(
				bg,
				0,
				0,
				*width,
				*height
			);

			StringFormat* format = new StringFormat(StringFormatFlagsNoFitBlackBox);

			UInt32 i = 0;
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
					format,
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
					black
				);
				
				if (i == 0)
				{
					spaceWidth = charSize.Width / 2;
				}

				charRect.Add(
					chars[i],
					Rectangle(
						(int)pos.X,
						(int)pos.Y,
						(int)(charSize.Width - spaceWidth),
						(int)pixelHeight
					)
				);

				pos.X += charSize.Width;
				i++;
			}

			delete(bg);
			delete(black);

			delete(g);
			delete(bmp);
			delete(font);
			delete(format);
			GdiplusShutdown(gdiplusToken);
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

			texture = new Texture(engine);
			texture->Create(512, 512, true);

			ID3D11ShaderResourceView* textureResource = (ID3D11ShaderResourceView*)texture->GetNativeResource();

			ID3D11Resource* res;
			textureResource->GetResource(&res);

			D3D11_MAPPED_SUBRESOURCE mapped;

			DllMain::Context->Map(res, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

			memcpy(mapped.pData, pixels, sizeof(DWORD) * width * height);

			DllMain::Context->Unmap(res, 0);
		}
		#pragma endregion
	}
}
