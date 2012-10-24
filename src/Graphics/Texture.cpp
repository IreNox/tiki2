
#include "Core/Engine.h"
#include "Graphics/Texture.h"

#include "Core/HelperLog.h"
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
			: ITexture(engine), texture(0), textureResource(0), dynamic(false)
		{
			ZeroMemory(
				&desc,
				sizeof(D3D11_TEXTURE2D_DESC)
			);
		}

		Texture::Texture(Engine* engine, ID3D11Texture2D* tex, bool dynamic)
			: ITexture(engine), texture(tex), dynamic(dynamic)
		{
			tex->GetDesc(&desc);

			D3D11_SHADER_RESOURCE_VIEW_DESC srDesc;
			ZeroMemory(&srDesc, sizeof(srDesc));

			srDesc.Format = desc.Format;
			srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srDesc.Texture2D.MostDetailedMip = 0;
			srDesc.Texture2D.MipLevels = 1;

			HRESULT r = DllMain::Device->CreateShaderResourceView(
				tex,
				&srDesc,
				&textureResource
			);
			
			// TODO: Can't create ShaderResourceView
			//if (FAILED(r))
			//{
			//	throw "Can't create ShaderResourceView";
			//}
		}

		Texture::~Texture()
		{
			SafeRelease(&texture);
		}
		#pragma endregion

		#pragma region Member
		bool Texture::GetDynamic()
		{
			return dynamic;
		}

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
		void Texture::Create(UInt32 width, UInt32 height, bool dynamic)
		{
			this->createInternal(width, height, dynamic);
		}

		void Texture::createInternal(UInt32 width, UInt32 height, bool dynamic)
		{
			if (this->GetReady()) return;

			this->dynamic = dynamic;

			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			desc.SampleDesc.Count = 1;
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

			if (dynamic)
			{
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			}
			else
			{
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.CPUAccessFlags = 0;
			}

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

			ID3D11Texture2D* oldTexture = texture;
			ID3D11ShaderResourceView* oldResource = textureResource;

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
				texture = oldTexture;
				textureResource = oldResource;

				HelperLog::WriteError("Can't load Texture", 0);
			}

			SafeRelease(&oldTexture);
			SafeRelease(&oldResource);

			ID3D11Resource* res;
			textureResource->GetResource(&res);

			texture = (ID3D11Texture2D*)res;
			texture->GetDesc(&desc);
		}

		void Texture::saveToStream(wcstring fileName, Stream* stream)
		{
			//ID3D10Blob* blob = 0;

			HRESULT r = D3DX11SaveTextureToFile(
				DllMain::Context,
				texture,
				D3DX11_IFF_JPG,
				fileName
			);

			if (FAILED(r))
			{
				HelperLog::WriteError("Can't save Texture", 0);
			}

			//stream->Write(
			//	blob->GetBufferPointer(),
			//	0,
			//	blob->GetBufferSize()
			//);

			//SafeRelease(&blob);
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

		Vector2 Texture::GetSize()
		{
			return Vector2(
				(float)desc.Width,
				(float)desc.Height
			);
		}

		Rectangle Texture::GetRectangle()
		{
			return Rectangle(0, 0, desc.Width, desc.Height);
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

