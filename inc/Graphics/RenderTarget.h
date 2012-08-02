#pragma once

#include "Core/IRenderTarget.h"

#include "Graphics/Texture.h"

namespace TikiEngine
{
	namespace Resources
	{
		class RenderTarget : public IRenderTarget, private Texture
		{
		public:

			RenderTarget(Engine* engine);
			RenderTarget(Engine* engine, ID3D11RenderTargetView* renderTarget);
			~RenderTarget();

			void Create(UInt32 width, UInt32 height);

			UInt32 AddRef();
			UInt32 Release();

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

			ID3D11RenderTargetView* renderTarget;

		};
	}
}