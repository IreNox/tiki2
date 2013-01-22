
#include "Core/Engine.h"
#include "Graphics/Texture.h"

#include "Core/HelperLog.h"
#include "Graphics/DllMain.h"

#include "Core/TypeGlobals.h"

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
				sizeof(TDX_Texture2D_Desc)
			);
		}

		Texture::Texture(Engine* engine, TDX_Texture2D* tex, bool createShaderView, bool dynamic)
			: ITexture(engine), texture(tex), dynamic(dynamic), textureResource(0)
		{
			tex->GetDesc(&desc);
						
			if (createShaderView)
			{
				TDX_ShaderResourceView_Desc srDesc;
				ZeroMemory(&srDesc, sizeof(srDesc));

#ifdef TIKI_DX10
				srDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
#else
				srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
#endif

				srDesc.Format = desc.Format;
				srDesc.Texture2D.MostDetailedMip = 0;
				srDesc.Texture2D.MipLevels = 1;

				HRESULT r = DllMain::Device->CreateShaderResourceView(
					tex,
					&srDesc,
					&textureResource
				);

				if (FAILED(r))
				{
					engine->HLog.WriteError("Can't create ShaderResourceView", 0);
				}
			}
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
		void Texture::Create(UInt32 width, UInt32 height, bool dynamic, PixelFormat format)
		{
			this->createInternal(width, height, dynamic, format);
		}

		void Texture::createInternal(UInt32 width, UInt32 height, bool dynamic, PixelFormat format)
		{
			if (this->GetReady()) return;

			this->dynamic = dynamic;

			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = (DXGI_FORMAT)format;
			desc.SampleDesc.Count = 1;

#if TIKI_DX10
			desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
#else
			desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
#endif

			if (dynamic)
			{
#if TIKI_DX10
				desc.Usage = D3D10_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
#else
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
#endif
			}
			else
			{
#if TIKI_DX10
				desc.Usage = D3D10_USAGE_DEFAULT;
#else
				desc.Usage = D3D11_USAGE_DEFAULT;
#endif
				desc.CPUAccessFlags = 0;
			}

			DllMain::Device->CreateTexture2D(
				&desc,
				0,
				&texture
			);
			texture->GetDesc(&this->desc);

			TDX_ShaderResourceView_Desc srDesc;
			ZeroMemory(&srDesc, sizeof(srDesc));
			
#if TIKI_DX10
			srDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
#else
			srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
#endif

			srDesc.Format = desc.Format;
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

			TDX_Texture2D* oldTexture = texture;
			TDX_ShaderResourceView* oldResource = textureResource;

#ifdef TIKI_DX10
			HRESULT r = D3DX10CreateShaderResourceViewFromMemory(
#else
			HRESULT r = D3DX11CreateShaderResourceViewFromMemory(
#endif
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

				engine->HLog.WriteError("Can't load Texture", 0);
			}

			SafeRelease(&oldTexture);
			SafeRelease(&oldResource);

			TDX_Resource* res;
			textureResource->GetResource(&res);

			texture = (TDX_Texture2D*)res;
			texture->GetDesc(&desc);
		}

		void Texture::saveToStream(wcstring fileName, Stream* stream)
		{
#if TIKI_DX11
			TDX_Texture2D_Desc desc;
			texture->GetDesc(&desc);

			desc.BindFlags = 0;
			desc.MiscFlags &= D3D11_RESOURCE_MISC_TEXTURECUBE;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			desc.Usage = D3D11_USAGE_STAGING;

			ID3D11Texture2D* tex;
			HRESULT r = DllMain::Device->CreateTexture2D(&desc, 0, &tex);

			if (FAILED(r))
			{
				engine->HLog.Write("Can't save Texture to File. Can't create Temp-Texture.");
				return;
			}
			DllMain::Context->CopyResource(tex, texture);

			D3D11_MAPPED_SUBRESOURCE mapped;
			if (DllMain::Context->Map(tex, 0, D3D11_MAP_READ, 0, &mapped))
			{
				engine->HLog.Write("Texture successful written to File. NOT!");

				DllMain::Context->Unmap(tex, 0);
			}
			else
			{
				engine->HLog.Write("Can't save Texture to File.");
			}

			tex->Release();
#endif
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

		Vector2 Texture::GetCenter()
		{
			return Vector2(
				(float)desc.Width / 2.0f,
				(float)desc.Height / 2.0f
			);
		}

		Rectangle Texture::GetRectangle()
		{
			return Rectangle(0, 0, desc.Width, desc.Height);
		}

		void Texture::GetData(PixelFormat format, void** data, UInt32* dataLength)
		{
			if (!dynamic)
			{
				engine->HLog.Write("GetData can only used for dynamic textures. Create Texture with dynamic flag.");
				return;
			}

			if (format != PF_A8R8G8B8)
			{
				engine->HLog.Write("GetData: Wrong Format");
				return;
			}

#if TIKI_DX10
			D3D10_MAPPED_TEXTURE2D mapped;
			HRESULT r = texture->Map(0, D3D10_MAP_READ, 0, &mapped);
#else
			D3D11_MAPPED_SUBRESOURCE mapped;
			HRESULT r = DllMain::Context->Map(texture, 0, D3D11_MAP_READ, 0, &mapped);
#endif
			
			if (FAILED(r))
			{
				engine->HLog.Write("Can't map Texture. Unknown Error.");
				return;
			}

			Byte* srcB = (Byte*)mapped.pData;
			Single* srcF = (Single*)mapped.pData;

			UInt32 i = 0;
			UInt32 c = desc.Width * desc.Height;
			Byte* pixels = new Byte[c * 4];
			
			while (i < c)
			{
				Byte* color = &pixels[i * 4];

				switch (desc.Format)
				{
				case DXGI_FORMAT_R8G8B8A8_UNORM:
					color[0] = (srcB + (i * 4))[0];
					color[1] = (srcB + (i * 4))[1];
					color[2] = (srcB + (i * 4))[2];
					color[3] = (srcB + (i * 4))[3];
					break;
				case DXGI_FORMAT_R32G32B32A32_FLOAT:
					color[0] = (Byte)((srcF + (i * 4))[0] * 255.0f);
					color[1] = (Byte)((srcF + (i * 4))[1] * 255.0f);
					color[2] = (Byte)((srcF + (i * 4))[2] * 255.0f);
					color[3] = (Byte)((srcF + (i * 4))[3] * 255.0f);
					break;
				}

				i++;
			}

#if TIKI_DX10
			texture->Unmap(0);
#else
			DllMain::Context->Unmap(texture, 0);
#endif

			*data = pixels;
			*dataLength = sizeof(Color) * desc.Width * desc.Height;
		}

		void Texture::SetData(PixelFormat format, void* data, UInt32 dataLength)
		{
			if (!dynamic)
			{
				engine->HLog.Write("SetData can only used for dynamic textures. Create Texture with dynamic flag");
				return;
			}

			if (format != PF_A8R8G8B8 || desc.Format != DXGI_FORMAT_R8G8B8A8_UNORM)
			{
				engine->HLog.Write("SetData: Wrong Format");
				return;
			}

#if TIKI_DX10
			D3D10_MAPPED_TEXTURE2D mapped;
			HRESULT r = texture->Map(0, D3D10_MAP_WRITE_DISCARD, 0, &mapped);
#else
			D3D11_MAPPED_SUBRESOURCE mapped;
			HRESULT r = DllMain::Context->Map(texture, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
#endif

			memcpy(
				mapped.pData,
				data,
				dataLength
			);

#if TIKI_DX10
			texture->Unmap(0);
#else
			DllMain::Context->Unmap(texture, 0);
#endif
		}
		#pragma endregion
	}
}

