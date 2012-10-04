#pragma once

#include "Core/IModelRenderer.h"

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

		class ModelRenderer : public IModelRenderer
		{
		public:
			ModelRenderer(Engine* engine, GameObject* gameObject);
			~ModelRenderer();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			IModel* GetMesh();
			Material* GetMaterial();

			void SetMesh(IModel* mesh);
			void SetMaterial(Material* material);

			bool GetDynamic();
			void SetDynamic(bool dynamic);

			bool GetReady();

		private:

			IModel* mesh;
			Material* material;

			VertexData* data;

			void updateData();

		};
	}
}