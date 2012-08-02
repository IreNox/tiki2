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
			~RenderTarget();

			void Create(UInt32 width, UInt32 height);

		protected:

			ID3D11RenderTargetView* renderTarget;

			void loadFromStream(wcstring fileName, Stream* stream);
		};
	}
}