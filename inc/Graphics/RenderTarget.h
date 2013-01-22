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
			RenderTarget(Engine* engine, TDX_RenderTargetView* renderTarget, bool shaderView);

			~RenderTarget();

			void Create(UInt32 width, UInt32 height, bool dynamic, PixelFormat format);
			void CreateScreenSize(bool dynamic = false, PixelFormat format = PF_R32G32B32A32);

			void SaveToFile(wcstring fileName);

			void Apply(UInt32 slot);
			void ApplyFirstAndOnly();
			void Clear(const Color& color);

			void Resize(UInt32 width, UInt32 height);

			/*! @brief Resize RenderTarget. Create no ShaderResourceView! */
			void Resize(TDX_RenderTargetView* renderTarget);

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
			TDX_RenderTargetView* renderTarget;

		};
	}
}