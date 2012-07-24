#pragma once

#include "Graphics/Buffer.h"

namespace TikiEngine
{
	namespace Buffer
	{
		class VertexBuffer : public Buffer
		{
		public:
			VertexBuffer(Engine* engine, VertexDeclaration* decl);
			~VertexBuffer();

		protected:
			void fillBufferDesc(D3D11_BUFFER_DESC* desc);
			ID3D11Buffer* createBuffer(UINT size, void* data);
		};
	}
}