
#include "Core/Engine.h"
#include "Graphics/Texture.h"

#include "Core/Console.h"
#include "Graphics/DllMain.h"

#include <d3d11.h>
#include <d3dx11.h>

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		Texture::Texture(Engine* engine)
			: ITexture(engine)
		{

		}

		Texture::~Texture()
		{
			if (texture != 0)
			{
				texture->Release();
				texture = 0;
			}
		}
		#pragma endregion

		#pragma region Member
		void* Texture::GetResource()
		{
			return (void*)texture;
		}

		bool Texture::GetReady()
		{
			return (texture != 0);
		}
		#pragma endregion

		#pragma region Member - Create
		void Texture::LoadFromFile(wstring fileName)
		{
			HRESULT r = D3DX11CreateShaderResourceViewFromFile(
				DllMain::Device,
				fileName.c_str(),
				0,
				0,
				&texture,
				0
			);

			if (FAILED(r))
			{
				Console::WriteError("Can't load Texture", r);
			}
		}

		void Texture::Create(Int32 width, Int32 height)
		{

		}
		#pragma endregion

		#pragma region Member - Data
		Int32 Texture::GetWidth()
		{
			return 0;
		}

		Int32 Texture::GetHeight()
		{
			return 0;
		}

		void GetData(Int32 format, void** data)
		{

		}

		void SetData(Int32 format, void* data, UInt32 dataLength)
		{

		}
		#pragma endregion


	}
}

