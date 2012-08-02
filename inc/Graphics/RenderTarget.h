#pragma once

#include "Core/IRenderTarget.h"

#include "Graphics/Texture.h"

namespace TikiEngine
{
	namespace Resources
	{
		class RenderTarget : public IRenderTarget, public Texture
		{
		public:

			RenderTarget(Engine* engine);
			RenderTarget(Engine* engine, ID3D11RenderTargetView* renderTarget);
			~RenderTarget();

			void Create(UInt32 width, UInt32 height);

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);

		private:

			ID3D11RenderTargetView* renderTarget;

		};
	}
}