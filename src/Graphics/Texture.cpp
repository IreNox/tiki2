
#include "Core/Engine.h"
#include "Graphics/Texture.h"

#include "Core/Console.h"
#include "Graphics/DllMain.h"

#include "Core/TypeFunc.h"

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
			SafeRelease(&texture);
		}
		#pragma endregion

		#pragma region Member
		void* Texture::GetNativeResource()
		{
			return (void*)texture;
		}

		bool Texture::GetReady()
		{
			return (texture != 0);
		}
		#pragma endregion

		#pragma region Member - Create
		void Texture::loadFromStream(Stream* stream)
		{
			UInt32 size = stream->GetLength();
			Byte* data = new Byte(size);

			stream->Read(data, 0, size);

			HRESULT r = D3DX11CreateShaderResourceViewFromMemory(
				DllMain::Device,
				data,
				size,
				0,
				0,
				&textureResource,
				0
			);

			if (FAILED(r))
			{
				Console::WriteError("Can't load Texture", r);
			}

			textureResource->QueryInterface<ID3D11Texture2D>(&texture);
			texture->GetDesc(&desc);
		}

		void Texture::saveToStream(Stream* stream)
		{
			ID3D10Blob* blob;

			HRESULT r = D3DX11SaveTextureToMemory(
				DllMain::Context,
				texture,
				D3DX11_IFF_PNG,
				&blob,
				0
			);

			if (FAILED(r))
			{
				Console::WriteError("Can't load Texture", r);
			}

			stream->Write(
				blob->GetBufferPointer(),
				0,
				blob->GetBufferSize()
			);

			SafeRelease(&blob);
		}
		#pragma endregion

		#pragma region Member - Data
		Int32 Texture::GetWidth()
		{
			return desc.Width;
		}

		Int32 Texture::GetHeight()
		{
			return desc.Height;
		}

		void Texture::GetData(Int32 format, void** data)
		{
			D3D11_MAPPED_SUBRESOURCE mapped;
			DllMain::Context->Map(texture, 0, D3D11_MAP_READ, 0, &mapped);

			for (UINT i = 0; i < desc.Width; i++)
			{
				for (UINT j = 0; j < desc.Height; j++)
				{
					//What code goes here to set the colour value for each pixel?    
				}
			}

			DllMain::Context->Unmap(texture, 0);
		}

		void Texture::SetData(Int32 format, void* data, UInt32 dataLength)
		{

		}
		#pragma endregion


	}
}

