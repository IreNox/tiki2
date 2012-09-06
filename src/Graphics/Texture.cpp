
#include "Core/Engine.h"
#include "Graphics/Texture.h"

#include "Core/Console.h"
#include "Graphics/DllMain.h"

#include "Core/TypeGlobals.h"

#include <d3d11.h>
#include <d3dx11.h>

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Texture::Texture(Engine* engine)
			: ITexture(engine)
		{

		}

		Texture::Texture(Engine* engine, ID3D11Texture2D* tex)
			: ITexture(engine), texture(tex)
		{
			tex->GetDesc(&desc);

			D3D11_SHADER_RESOURCE_VIEW_DESC srDesc;
			ZeroMemory(&srDesc, sizeof(srDesc));

			srDesc.Format = desc.Format;
			srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srDesc.Texture2D.MostDetailedMip = 0;
			srDesc.Texture2D.MipLevels = 1;

			DllMain::Device->CreateShaderResourceView(
				tex,
				&srDesc,
				&textureResource
			);
		}

		Texture::~Texture()
		{
			SafeRelease(&texture);
		}
		#pragma endregion

		#pragma region Member
		void* Texture::GetNativeResource()
		{
			return (void*)textureResource;
		}

		bool Texture::GetReady()
		{
			return (texture != 0);
		}
		#pragma endregion

		#pragma region Member - Create
		void Texture::Create(UInt32 width, UInt32 height)
		{
			this->createInternal(width, height, 0);
		}

		void Texture::createInternal(UInt32 width, UInt32 height, UInt32 bindFlags)
		{
			if (this->GetReady()) return;

			D3D11_TEXTURE2D_DESC desc;
			ZeroMemory(&desc, sizeof(desc));

			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = bindFlags | D3D11_BIND_SHADER_RESOURCE;

			DllMain::Device->CreateTexture2D(
				&desc,
				0,
				&texture
			);
			texture->GetDesc(&this->desc);

			D3D11_SHADER_RESOURCE_VIEW_DESC srDesc;
			ZeroMemory(&srDesc, sizeof(srDesc));

			srDesc.Format = desc.Format;
			srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srDesc.Texture2D.MostDetailedMip = 0;
			srDesc.Texture2D.MipLevels = 1;

			DllMain::Device->CreateShaderResourceView(
				texture,
				&srDesc,
				&textureResource
			);
		}

		void Texture::loadFromStream(wcstring fileName, Stream* stream)
		{
			UPInt size = stream->GetLength();
			Byte* data = new Byte[size];

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

			delete[](data);

			if (FAILED(r))
			{
				Console::WriteError("Can't load Texture", r);
			}

			ID3D11Resource* res;
			textureResource->GetResource(&res);

			texture = (ID3D11Texture2D*)res;
			texture->GetDesc(&desc);
		}

		void Texture::saveToStream(wcstring fileName, Stream* stream)
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
				Console::WriteError("Can't save Texture", r);
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
					//What code goes here to set the color value for each pixel?    
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

