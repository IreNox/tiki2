
#include "Graphics/MeshRenderer.h"

namespace TikiEngine
{
	namespace Components
	{
		#pragma region Class
		MeshRenderer::MeshRenderer(Engine* engine, GameObject* gameObject)
			: IMeshRenderer(engine, gameObject), mesh(0), material(0)
		{
			data = new VertexData(engine);
		}

		MeshRenderer::~MeshRenderer()
		{
			if (mesh != 0) mesh->Release();
			if (material != 0) material->Release();

			delete(data);
		}
		#pragma endregion

		#pragma region Member
		bool MeshRenderer::GetReady()
		{
			return (mesh != 0 && mesh->GetReady()) && (material != 0 && material->GetReady());
		}
		#pragma endregion

		#pragma region Member - Get/Set
		Mesh* MeshRenderer::GetMesh()
		{
			return mesh;
		}

		Material* MeshRenderer::GetMaterial()
		{
			return material;
		}

		void MeshRenderer::SetMesh(Mesh* mesh)
		{
			if (this->mesh != 0)
			{
				this->mesh->Release();
			}

			this->mesh = mesh;

			if (this->mesh != 0)
			{
				this->mesh->AddRef();
			}

			updateData();
		}

		void MeshRenderer::SetMaterial(Material* material)
		{
			if (this->material != 0)
			{
				this->material->Release();
			}

			this->material = material;

			if (this->material != 0)
			{
				this->material->AddRef();
			}

			updateData();
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void MeshRenderer::Draw(const DrawArgs& args)
		{			
			if (!this->GetReady()) return;

			material->UpdateDrawArgs(args);

			data->Apply();
			data->Draw();
		}

		void MeshRenderer::Update(const UpdateArgs& args)
		{
			//if (!this->GetReady()) return;
		}
		#pragma endregion

		#pragma region Private Member
		void MeshRenderer::updateData()
		{
			if (!this->GetReady()) return;

			data->SetData(
				mesh,
				(Shader*)material->GetShader()
			);
		}
		#pragma endregion		
	}
}