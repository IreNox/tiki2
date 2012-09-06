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
			RenderTarget(Engine* engine, ID3D11RenderTargetView* renderTarget);
			~RenderTarget();

			void Create(UInt32 width, UInt32 height);
			void CreateScreenSize();

			void Apply(UInt32 slot);
			void Clear(const Color& color);

			Int32 GetWidth();
			Int32 GetHeight();

			void GetData(Int32 format, void** data);
			void SetData(Int32 format, void* data, UInt32 dataLength);

			void* GetNativeResource();

			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

			Texture* texture;

			ID3D11RenderTargetView* renderTarget;

		};
	}
}