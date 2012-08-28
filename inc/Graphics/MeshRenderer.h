#pragma once

#include "Core/IMeshRenderer.h"

#include "Graphics/Shader.h"
#include "Graphics/VertexData.h"
#include "Graphics/VertexDeclaration.h"

#include <d3d11.h>
#include <D3DX11.h>

namespace TikiEngine
{
	namespace Components
	{
		using namespace TikiEngine::Vertices;

		class MeshRenderer : public IMeshRenderer
		{
		public:
			MeshRenderer(Engine* engine, GameObject* gameObject);
			~MeshRenderer();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			Mesh* GetMesh();
			Material* GetMaterial();

			void SetMesh(Mesh* mesh);
			void SetMaterial(Material* material);

			bool GetDynamic();
			void SetDynamic(bool dynamic);

			bool GetReady();

		private:

			Mesh* mesh;
			Material* material;

			VertexData* data;

			void updateData();
			
		};
	}
}