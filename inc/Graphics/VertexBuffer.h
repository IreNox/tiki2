#pragma once

#include "Graphics/Buffer.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class VertexBuffer : public Buffer
		{
		public:
			VertexBuffer(Engine* engine, UInt32 vertexSize, bool dynamic);
			VertexBuffer(Engine* engine, VertexDeclaration* decl, bool dynamic);
			~VertexBuffer();

		protected:
			
			ID3D11Buffer* createBuffer(UINT size, void* data);

		private:

			bool dynamic;
		};
	}
}