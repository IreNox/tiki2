#pragma once

#include "Core/TypeGlobals.h"

#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"
#include "Graphics/TikiBone.h"

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

		class TikiMesh : public EngineObject
		{
		public:

			TikiMesh(Engine* engine);
			~TikiMesh();

			void Draw(const DrawArgs& args, Model* model, GameObject* gameObject);

			void GetIndexData(UInt32** data, UInt32* count);
			void SetIndexData(const UInt32* data, UInt32 count);

			void GetAdjacencyIndexData(UInt32** data, UInt32* count);
			void SetAdjacencyIndexData(const UInt32* data, UInt32 count);

			void GetVertexData(void** data, UInt32* length);
			void SetVertexData(const void* data, UInt32 length);

			inline const string& GetName() { return name; }
			inline void SetName(const string& name) { this->name = name; }

			inline void SetDeformation(bool b) { hasDeformation = b; }
			inline bool UseDeformation() { return hasDeformation; }

			inline void SetAdjacencyIndices(bool b) { hasAdjacencyIndices = b; }
			inline bool HasAdjacencyIndices() { return hasAdjacencyIndices; }

			Material* GetMaterial();
			void SetMaterial(Material* material);

			bool GetReady();

		private:

			string name;

			Material* material;

			bool hasDeformation;
			bool hasAdjacencyIndices;

			void* vertexData;
			UInt32 vertexLength;

			UInt32* indexData;
			UInt32 indexCount;

			UInt32* adjacencyIndexData;
			UInt32 adjacencyIndexCount;

#ifdef TIKI_ENGINE
			StaticBuffer<D3D11_BIND_INDEX_BUFFER>* indexBuffer;
			StaticBuffer<D3D11_BIND_INDEX_BUFFER>* indexAdjacencyBuffer;

			StaticBuffer<D3D11_BIND_VERTEX_BUFFER>* vertexBuffer;

			VertexDeclaration* decl;
#endif

		};
	}
}
