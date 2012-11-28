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

		class TikiMesh : public TikiObject
		{

		public:

			TikiMesh(Model* model);
			~TikiMesh();

			void Draw(const DrawArgs& args, GameObject* gameObject);

			void GetIndexData(UInt32** data, UInt32* count);
			void SetIndexData(const UInt32* data, UInt32 count);

			void GetVertexData(void** data, UInt32* length);
			void SetVertexData(const void* data, UInt32 length);

			string GetName();
			void SetName(string name);

			void SetDeformation(bool b);
			bool UseDeformation();

			Material* GetMaterial();
			void SetMaterial(Material* material);

			bool GetReady();

		private:

			Model* model;

			string name;

			Material* material;
			bool hasDeformation;

			void* vertexData;
			UInt32 vertexLength;

			UInt32* indexData;
			UInt32 indexCount;

#ifdef TIKI_ENGINE
			StaticBuffer<D3D11_BIND_INDEX_BUFFER>* indexBuffer;
			StaticBuffer<D3D11_BIND_VERTEX_BUFFER>* vertexBuffer;

			VertexDeclaration* decl;
#endif

		};
	}
}
