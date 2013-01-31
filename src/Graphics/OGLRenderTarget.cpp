
#include "Graphics/RenderTarget.h"

#include "Graphics/DllMain.h"
#include "Graphics/OGLGraphicsModule.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		RenderTarget::RenderTarget(Engine* engine)
			: IRenderTarget(engine), renderTarget(0), texture(0)
		{
		}

		RenderTarget::RenderTarget(Engine* engine, UInt32 textureId)
			: IRenderTarget(engine)
		{
			texture = TIKI_NEW Texture(engine, textureId);
			renderTarget = textureId;
		}

		RenderTarget::~RenderTarget()
		{
			DllMain::ModuleGraphics->RemoveScreenSizeRenderTarget(this);

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
			this->ApplyFirstAndOnly();
			glClearColor(color.R, color.G, color.B, color.A);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void RenderTarget::Resize(UInt32 width, UInt32 height)
		{
			//DXGI_FORMAT format = texture->desc.Format;

			//SafeRelease(&texture);
			//SafeRelease(&renderTarget);

			//this->Create(width, height, false, (PixelFormat)format);
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

		Vector2 RenderTarget::GetCenter()
		{
			return texture->GetCenter();
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
			return texture != 0 && texture->GetReady();
		}
		#pragma endregion

		#pragma region Member - Create
		void RenderTarget::Create(UInt32 width, UInt32 height, bool dynamic, PixelFormat format)
		{
			if (this->GetReady())
				return;

			texture = TIKI_NEW Texture(engine);
			texture->Create(width, height, dynamic, format);
			texture->AddRef();
			
			renderTarget = *((UInt32*)texture->GetNativeResource());
		}

		void RenderTarget::CreateScreenSize(bool dynamic, PixelFormat format)
		{
			this->Create(
				DllMain::ModuleGraphics->GetViewPort()->Width,
				DllMain::ModuleGraphics->GetViewPort()->Height,
				dynamic,
				format
			);

			DllMain::ModuleGraphics->AddScreenSizeRenderTarget(this);
		}
		#pragma endregion

		#pragma region Protected Member
		void RenderTarget::loadFromStream(wcstring fileName, Stream* stream)
		{
			texture->loadFromStream(fileName, stream);
		}

		void RenderTarget::saveToStream(wcstring fileName, Stream* stream)
		{
			texture->saveToStream(fileName, stream);
		}
		#pragma endregion
	}
}