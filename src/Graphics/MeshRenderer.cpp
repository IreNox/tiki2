
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
			SafeRelease(&mesh);
			SafeRelease(&material);

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
			SafeRelease(&this->mesh);

			this->mesh = mesh;
			SafeAddRef(&this->mesh);

			updateData();
		}

		void MeshRenderer::SetMaterial(Material* material)
		{
			SafeRelease(&this->material);

			this->material = material;
			SafeAddRef(&this->material);

			updateData();
		}

		bool MeshRenderer::GetDynamic()
		{
			return data->GetDynamic();
		}

		void MeshRenderer::SetDynamic(bool dynamic)
		{
			data->SetDynamic(dynamic);
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void MeshRenderer::Draw(const DrawArgs& args)
		{			
			if (!this->GetReady()) return;

			material->UpdateDrawArgs(args, gameObject);

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