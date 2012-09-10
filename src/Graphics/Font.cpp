
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
	namespace Graphics
	{
		#pragma region Class
		Font::Font(Engine* engine)
			: EngineObject(engine), texture(0)
		{
		}

		Font::~Font()
		{
			SafeRelease(&texture);
		}
		#pragma endregion

		#pragma region Member - Create
		void Font::Create(wcstring fontName)
		{
			int width = 512;
			int height = 512;

			int stride = 4 * width;
			BYTE* pixels = new BYTE[stride * height];
			ZeroMemory(pixels, stride * height);
			
			ULONG_PTR           gdiplusToken;  
			GdiplusStartupInput gdiplusStartupInput;
			GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

			Bitmap* bmp = new Bitmap(width, height, stride, PixelFormat32bppARGB, pixels);
			Gdiplus::Graphics* g = Gdiplus::Graphics::FromImage(bmp);
			
			auto c = Gdiplus::Color::Transparent;

			SolidBrush* bg = new SolidBrush(Gdiplus::Color(128.0f, 255.0f, 0.0f, 0.0f));				
			SolidBrush* blue = new SolidBrush(Gdiplus::Color::Blue);

			g->FillRectangle(
				bg,
				0,
				0,
				width,
				height
			);

			g->FillRectangle(
				blue,
				10,
				10,
				100,
				100
			);
			
			delete(bg);
			delete(blue);

			delete(g);

			texture = new Texture(engine);
			texture->Create(512, 512, true);

			ID3D11ShaderResourceView* textureResource = (ID3D11ShaderResourceView*)texture->GetNativeResource();

			ID3D11Resource* res;
			textureResource->GetResource(&res);

			D3D11_MAPPED_SUBRESOURCE mapped;

			DllMain::Context->Map(res, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);

			memcpy(mapped.pData, pixels, stride * height);

			DllMain::Context->Unmap(res, 0);

			delete(bmp);
			GdiplusShutdown(gdiplusToken);
		}
		#pragma endregion

		#pragma region Member
		float Font::GetHeight()
		{
			return maxHeight;
		}

		ITexture* Font::GetTexture()
		{
			return texture;
		}
		#pragma endregion

		#pragma region Member - Draw
		float Font::DrawChar(wchar_t c, const Vector2& pos)
		{
			float width = 0;

			DllMain::ModuleSpriteBatch->Draw(texture, pos);

			return width;
		}
		#pragma endregion


	}
}
