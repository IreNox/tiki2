
#include "Graphics/MeshRenderer.h"

namespace TikiEngine
{
	namespace Components
	{
		#pragma region Class
		MeshRenderer::MeshRenderer(Engine* engine, GameObject* gameObject)
			: IMeshRenderer(engine, gameObject), mesh(0), material(0), decl(0), indexBuffer(0), vertexBuffer(0)
		{
		}

		MeshRenderer::~MeshRenderer()
		{
			SafeRelease(&mesh);
			SafeRelease(&material);
			SafeRelease(&decl);

			SafeRelease(&indexBuffer);
			SafeRelease(&vertexBuffer);
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
			SafeAddRef(mesh, &this->mesh);

			updateData(true, false);
		}

		void MeshRenderer::SetMaterial(Material* material)
		{
			SafeRelease(&this->material);
			SafeAddRef(material, &this->material);

			updateData(false, true);
		}
		#pragma endregion

		#pragma region Member - Update
		void MeshRenderer::Update(const UpdateArgs& args)
		{			
		}
		#pragma endregion

		#pragma region Private Member
		void MeshRenderer::updateData(bool udMesh, bool udMaterial)
		{
			if (!this->GetReady()) return;

			SafeRelease(&decl);

			decl = TIKI_NEW VertexDeclaration(
				engine,
				material->GetShader(),
				mesh->GetVertexDeclaration()->GetInternalData(),
				mesh->GetVertexDeclaration()->Count()
				);

			if (udMesh)
			{
				SafeRelease(&indexBuffer);
				SafeRelease(&vertexBuffer);

				UInt32 lenCount;
				void* vertexData = 0;
				mesh->GetVertexData(&vertexData, &lenCount);

				vertexBuffer = TIKI_NEW StaticBuffer<TIKI_VERTEX_BUFFER>(
					engine,
					decl->GetElementSize(),
					lenCount / decl->GetElementSize(),
					vertexData
					);

				UInt32* indexData;
				mesh->GetIndexData(&indexData, &lenCount);

				if (lenCount != 0)
				{
					indexBuffer = TIKI_NEW StaticBuffer<TIKI_INDEX_BUFFER>(
						engine,
						sizeof(UInt32),
						lenCount,
						indexData
						);
				}
			}
		}
		#pragma endregion		
	}
}