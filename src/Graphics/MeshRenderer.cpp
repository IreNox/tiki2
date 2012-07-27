
#include "Graphics/MeshRenderer.h"

namespace TikiEngine
{
	namespace Components
	{
		#pragma region Class
		MeshRenderer::MeshRenderer(Engine* engine, GameObject* gameObject)
			: IMeshRenderer(engine, gameObject)
		{
		}

		MeshRenderer::~MeshRenderer()
		{

		}
		#pragma endregion

		#pragma region Member
		bool MeshRenderer::GetReady()
		{
			return (mesh != 0) && (material != 0);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		IMesh* MeshRenderer::GetMesh()
		{
			return mesh;
		}

		Material* MeshRenderer::GetMaterial()
		{
			return material;
		}

		void MeshRenderer::SetMesh(IMesh* mesh)
		{
			if (this->mesh != 0)
			{
				this->mesh->Release();
			}

			this->mesh = (Mesh*)mesh;

			if (this->mesh != 0)
			{
				this->mesh->AddRef();
			}
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
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void MeshRenderer::Draw(const DrawArgs& args)
		{

		}

		void MeshRenderer::Update(const UpdateArgs& args)
		{

		}
		#pragma endregion
	}
}