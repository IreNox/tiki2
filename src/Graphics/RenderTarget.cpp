
#include "Graphics/RenderTarget.h"

#include "Graphics/DllMain.h"
#include "Graphics/GraphicsModule.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		RenderTarget::RenderTarget(Engine* engine)
			: IRenderTarget(engine), renderTarget(0), texture(0)
		{
		}

		RenderTarget::RenderTarget(Engine* engine, ID3D11RenderTargetView* renderTarget, bool shaderView)
			: IRenderTarget(engine), renderTarget(renderTarget), texture(0)
		{
			ID3D11Resource* res = 0;
			renderTarget->GetResource(&res);

			ID3D11Texture2D* tex = (ID3D11Texture2D*)res;
			texture = new Texture(engine, tex, shaderView, false);
		}

		RenderTarget::~RenderTarget()
		{
			DllMain::ModuleGraphics->RemoveScreenSizeRenderTarget(this);

			SafeRelease(&renderTarget);
			SafeRelease(&texture);
		}
		#pragma endregion

		#pragma region Member
		void RenderTarget::Apply(UInt32 slot)
		{
			DllMain::ModuleGraphics->SetRenderTarget(slot, renderTarget);
		}

		void RenderTarget::ApplyFirstAndOnly()
		{
			DllMain::ModuleGraphics->SetFirstAndOnlyRenderTargets(renderTarget);
		}

		void RenderTarget::Clear(const Color& color)
		{
			DllMain::Context->ClearRenderTargetView(renderTarget, color.arr);
		}

		void RenderTarget::Resize(UInt32 width, UInt32 height)
		{
			SafeRelease(&texture);
			SafeRelease(&renderTarget);

			this->Create(width, height, false);
		}

		void RenderTarget::Resize(ID3D11RenderTargetView* renderTarget)
		{
			SafeRelease(&texture);

			this->renderTarget = renderTarget;

			ID3D11Resource* res = 0;
			renderTarget->GetResource(&res);

			ID3D11Texture2D* tex = (ID3D11Texture2D*)res;
			texture = new Texture(engine, tex, false, false);
		}

		void RenderTarget::SaveToFile(wcstring fileName)
		{
			texture->SaveToFile(fileName);
		}

		Int32 RenderTarget::GetWidth()
		{
			return texture->GetWidth();
		}

		Int32 RenderTarget::GetHeight()
		{
			return texture->GetHeight();
		}

		Vector2 RenderTarget::GetSize()
		{
			return texture->GetSize();
		}

		Rectangle RenderTarget::GetRectangle()
		{
			return texture->GetRectangle();
		}

		bool RenderTarget::GetDynamic()
		{
			return texture->GetDynamic();
		}

		void RenderTarget::GetData(PixelFormat format, void** data, UInt32* dataLength)
		{
			texture->GetData(format, data, dataLength);
		}

		void RenderTarget::SetData(PixelFormat format, void* data, UInt32 dataLength)
		{
			texture->SetData(format, data, dataLength);
		}

		void* RenderTarget::GetNativeResource()
		{
			return texture->GetNativeResource();
		}

		bool RenderTarget::GetReady()
		{
			return texture != 0 && texture->GetReady() && (renderTarget != 0);
		}
		#pragma endregion

		#pragma region Member - Create
		void RenderTarget::Create(UInt32 width, UInt32 height, bool dynamic)
		{
			if (this->GetReady()) return;

			ID3D11Texture2D* texture;

			D3D11_TEXTURE2D_DESC desc;
			ZeroMemory(&desc, sizeof(desc));

			desc.Width = width;
			desc.Height = height;
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			desc.SampleDesc.Count = 1;
			desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

			if (dynamic)
			{
				desc.Usage = D3D11_USAGE_STAGING;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
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
						
			this->texture = new Texture(engine, texture, true, dynamic);

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

		void RenderTarget::CreateScreenSize(bool dynamic)
		{
			this->Create(
				DllMain::ModuleGraphics->GetViewPort()->Width,
				DllMain::ModuleGraphics->GetViewPort()->Height,
				dynamic
			);

			DllMain::ModuleGraphics->AddScreenSizeRenderTarget(this);
		}
		#pragma endregion

		#pragma region Protected Member
		void RenderTarget::loadFromStream(wcstring fileName, Stream* stream)
		{
			//texture->loadFromStream(fileName, stream);

			//D3D11_RENDER_TARGET_VIEW_DESC rtDesc;
			//rtDesc.Format = desc.Format;
			//rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			//rtDesc.Texture2D.MipSlice = 0;

			//DllMain::Device->CreateRenderTargetView(
			//	texture->GetNativeResource(),
			//	&rtDesc,
			//	&renderTarget
			//);
		}

		void RenderTarget::saveToStream(wcstring fileName, Stream* stream)
		{
		}
		#pragma endregion
	}
}