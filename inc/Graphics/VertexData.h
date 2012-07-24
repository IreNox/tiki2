#pragma once

#include "Graphics/Shader.h"

#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBuffer.h"

#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	namespace Vertices
	{
		using namespace TikiEngine::Buffer;
		using namespace TikiEngine::Effects;

		class VertexData
		{
		public:
			UINT indexIndex;
			UINT indexVertex;

			UINT countIndex;
			UINT countVertex;

			VertexData(Engine* engine, Shader* shader, VertexDeclaration* decl);
			~VertexData();

			void Apply();

			void SetIndexData(void* data, UINT size);
			void SetVertexData(void* data, UINT size);

		private:
			Engine* engine;

			bool allocatedIndex;
			bool allocatedVertex;

			IndexBuffer* indexBuffer;
			VertexBuffer* vertexBuffer;

			Shader* shader;
			VertexDeclaration* decl;

			void setData(TikiEngine::Buffer::Buffer* buffer, void* data, UINT size, bool* allocated, UINT* index, UINT* count);
		};
	}
}