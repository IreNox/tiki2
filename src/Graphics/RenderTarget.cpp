
#include "Graphics/RenderTarget.h"
#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		RenderTarget::RenderTarget(Engine* engine)
			: IRenderTarget(engine), Texture(engine), renderTarget(0)
		{
		}

		RenderTarget::RenderTarget(Engine* engine, ID3D11RenderTargetView* renderTarget)
			: IRenderTarget(engine), Texture(engine), renderTarget(renderTarget)
		{
			ID3D11Resource* res = 0;
			renderTarget->GetResource(&res);

			texture = (ID3D11Texture2D*)res;
			texture->GetDesc(&desc);

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

		RenderTarget::~RenderTarget()
		{
		}
		#pragma endregion

		#pragma region Member
		Int32 RenderTarget::GetWidth()
		{
			return Texture::GetWidth();
		}

		Int32 RenderTarget::GetHeight()
		{
			return Texture::GetHeight();
		}

		void RenderTarget::GetData(Int32 format, void** data)
		{
			Texture::GetData(format, data);
		}

		void RenderTarget::SetData(Int32 format, void* data, UInt32 dataLength)
		{
			Texture::SetData(format, data, dataLength);
		}

		void* RenderTarget::GetNativeResource()
		{
			return Texture::GetNativeResource();
		}

		bool RenderTarget::GetReady()
		{
			return Texture::GetReady() && (renderTarget != 0);
		}
		#pragma endregion

		#pragma region Member - Object
		UInt32 RenderTarget::AddRef()
		{
			Texture::AddRef();
			return IRenderTarget::AddRef();
		}

		UInt32 RenderTarget::Release()
		{
			Texture::Release();
			return IRenderTarget::Release();
		}
		#pragma endregion

		#pragma region Member - Create
		void RenderTarget::Create(UInt32 width, UInt32 height)
		{
			Texture::createInternal(width, height, D3D11_BIND_RENDER_TARGET);
		}
		#pragma endregion

		#pragma region Protected Member
		void RenderTarget::loadFromStream(wcstring fileName, Stream* stream)
		{
			Texture::loadFromStream(fileName, stream);

			D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
			rtDesc.Format = desc.Format;
			rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtDesc.Texture2D.MipSlice = 0;

			DllMain::Device->CreateRenderTargetView(
				texture,
				&rtDesc,
				&renderTarget
			);
		}

		void RenderTarget::saveToStream(wcstring fileName, Stream* stream)
		{
			Texture::saveToStream(fileName, stream);
		}
		#pragma endregion
	}
}