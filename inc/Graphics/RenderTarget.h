#pragma once

#include "Core/TypeGlobals.h"
#include "Core/IRenderTarget.h"

#include "Graphics/Texture.h"

namespace TikiEngine
{
	namespace Resources
	{
		class RenderTarget : public IRenderTarget
		{
		public:

			RenderTarget(Engine* engine);
#if TIKI_DX10 || TIKI_DX11
			RenderTarget(Engine* engine, TDX_RenderTargetView* renderTarget, bool shaderView);
#elif TIKI_OGL
			RenderTarget(Engine* engine, UInt32 textureId);
#endif

			~RenderTarget();

			void Create(UInt32 width, UInt32 height, bool dynamic, PixelFormat format);
			void CreateScreenSize(bool dynamic = false, PixelFormat format = PF_R32G32B32A32);

			void Apply(UInt32 slot);
			void ApplyFirstAndOnly();
			void Clear(const Color& color);

			void Resize(UInt32 width, UInt32 height);

#if TIKI_DX10 || TIKI_DX11
			/*! @brief Resize RenderTarget. Create no ShaderResourceView! */
			void Resize(TDX_RenderTargetView* renderTarget);
#endif

			Int32 GetWidth();
			Int32 GetHeight();
			Vector2 GetSize();
			Vector2 GetCenter();
			Rectangle GetRectangle();

			bool GetDynamic();

			void GetData(PixelFormat format, void** data, UInt32* dataLength);
			void SetData(PixelFormat format, void* data, UInt32 dataLength);

			void* GetNativeResource();

			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

			Texture* texture;

#if TIKI_DX10 || TIKI_DX11
			TDX_RenderTargetView* renderTarget;
#elif TIKI_OGL
			UInt32 renderTarget;
#endif

		};
	}
}