#pragma once

#include "Graphics/Buffer.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class IndexBuffer : public Buffer
		{
		public:
			IndexBuffer(Engine* engine);
			~IndexBuffer();

		protected:

			ID3D11Buffer* createBuffer(UINT size, void* data);
		};
	}
}