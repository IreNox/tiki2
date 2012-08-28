#pragma once

#include "Core/EngineObject.h"

#include "Graphics/Shader.h"
#include "Graphics/IndexBuffer.h"
#include "Graphics/VertexBuffer.h"

#include "Core/Mesh.h"
#include "Core/MeshIndexed.h"

namespace TikiEngine
{
	namespace Vertices
	{
		using namespace TikiEngine::Graphics;
		using namespace TikiEngine::Resources;

		class VertexData : public EngineObject
		{
		public:
			
			VertexData(Engine* engine);
			~VertexData();

			void Apply();
			void Draw();

			Mesh* GetMesh();
			void SetData(Mesh* mesh, Shader* material);

			bool GetDynamic();
			void SetDynamic(bool dynamic);

		private:

			bool dynamic;

			UInt32 indexIndex;
			UInt32 indexVertex;

			UInt32 countIndex;
			UInt32 countVertex;

			bool useIndex;
			bool allocatedIndex;
			bool allocatedVertex;

			IndexBuffer* indexBuffer;
			VertexBuffer* vertexBuffer;

			Mesh* mesh;

			Shader* shader;
			VertexDeclaration* decl;

			void setData(Buffer* buffer, void* data, UInt32 size, bool* allocated, UInt32* index, UInt32* count);
		};
	}
}