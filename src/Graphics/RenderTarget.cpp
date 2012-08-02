
#include "Graphics/RenderTarget.h"
#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Resources
	{
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
		}

		RenderTarget::~RenderTarget()
		{
		}

		void RenderTarget::Create(UInt32 width, UInt32 height)
		{
			Texture::createInternal(width, height, D3D11_BIND_RENDER_TARGET);
		}

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
	}
}