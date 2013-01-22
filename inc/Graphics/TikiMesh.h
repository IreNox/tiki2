#pragma once

#include "Core/TypeGlobals.h"

#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"
#include "Core/IModelMesh.h"

#ifdef TIKI_ENGINE
#include "Graphics/StaticBuffer.h"
#include "Graphics/VertexDeclaration.h"
#endif

using namespace TikiEngine::Vertices;

namespace TikiEngine
{
	namespace Resources
	{
		class Model;

		class TikiMesh : public IModelMesh
		{
		public:

#ifdef TIKI_ENGINE
			TikiMesh(Engine* engine);
#else
			TikiMesh();
#endif
			~TikiMesh();

			void Draw(const DrawArgs& args, Model* model, GameObject* gameObject);

			void SetIndexData(const UInt32* data, UInt32 count);
			void SetVertexData(const void* data, UInt32 dataLength);

			void GetAdjacencyIndexData(UInt32** data, UInt32* count);
			void SetAdjacencyIndexData(const UInt32* data, UInt32 count);

			const string& GetName() { return name; }
			inline void SetName(const string& name) { this->name = name; }

			inline void SetDeformation(bool b) { hasDeformation = b; }
			inline bool UseDeformation() { return hasDeformation; }

			inline void SetAdjacencyIndices(bool b) { hasAdjacencyIndices = b; }
			inline bool HasAdjacencyIndices() { return hasAdjacencyIndices; }

			Material* GetMaterial();
			void SetMaterial(Material* material);

			Matrix& GetLocalMatrix() { return localMatrix; }
			void SetLocalMatrix(const Matrix& matrix) { localMatrix = matrix; }

			bool GetVisible() { return visible; }
			void SetVisible(bool vis) { visible = vis; }

			bool GetReady();

		private:
						
			string name;

			bool visible;

			Matrix localMatrix;
			Material* material;

			bool hasDeformation;
			bool hasAdjacencyIndices;

			UInt32* adjacencyIndexData;
			UInt32 adjacencyIndexCount;

#ifdef TIKI_ENGINE
			StaticBuffer<TIKI_INDEX_BUFFER>* indexBuffer;
			StaticBuffer<TIKI_INDEX_BUFFER>* indexAdjacencyBuffer;

			StaticBuffer<TIKI_VERTEX_BUFFER>* vertexBuffer;

			VertexDeclaration* decl;
#endif

		};
	}
}
