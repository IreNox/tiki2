//
//#include "Graphics/ModelRenderer.h"
//
//namespace TikiEngine
//{
//	namespace Components
//	{
//#pragma region Class
//		ModelRenderer::ModelRenderer(Engine* engine, GameObject* gameObject)
//			: IModelRenderer(engine, gameObject), mesh(0), material(0)
//		{
//			data = new VertexData(engine);
//		}
//
//		ModelRenderer::~ModelRenderer()
//		{
//			SafeRelease(&data);
//			SafeRelease(&mesh);
//			SafeRelease(&material);
//		}
//#pragma endregion
//
//#pragma region Member
//		bool ModelRenderer::GetReady()
//		{
//			return (mesh != 0 && mesh->GetReady()) && (material != 0 && material->GetReady());
//		}
//#pragma endregion
//
//#pragma region Member - Get/Set
//		IModel* ModelRenderer::GetMesh()
//		{
//			return mesh;
//		}
//
//		Material* ModelRenderer::GetMaterial()
//		{
//			return material;
//		}
//
//		void ModelRenderer::SetMesh(IModel* mesh)
//		{
//			SafeRelease(&this->mesh);
//			SafeAddRef(mesh, &this->mesh);
//
//			updateData();
//		}
//
//		void ModelRenderer::SetMaterial(Material* material)
//		{
//			SafeRelease(&this->material);
//
//			this->material = material;
//			SafeAddRef(&this->material);
//
//			updateData();
//		}
//
//		bool ModelRenderer::GetDynamic()
//		{
//			return data->GetDynamic();
//		}
//
//		void ModelRenderer::SetDynamic(bool dynamic)
//		{
//			data->SetDynamic(dynamic);
//		}
//#pragma endregion
//
//#pragma region Member - Draw/Update
//		void ModelRenderer::Draw(const DrawArgs& args)
//		{			
//			if (!this->GetReady()) return;
//
//			material->UpdateDrawArgs(args, gameObject);
//
//			data->Apply();
//			data->Draw();
//		}
//
//		void ModelRenderer::Update(const UpdateArgs& args)
//		{
//
//			//if (!this->GetReady()) return;
//		}
//#pragma endregion
//
//#pragma region Private Member
//		void ModelRenderer::updateData()
//		{
//			if (!this->GetReady()) return;
//
//			data->SetData(
//				mesh,
//				(Shader*)material->GetShader()
//				);
//		}
//#pragma endregion		
//	}
//}