
#include "Graphics/Model.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"
#include "Core/IContentManager.h"
#include "Core/LibraryManager.h"
#include "Core/ISpriteBatch.h"

#include "Graphics/DllMain.h"
#include "Graphics/TikiMesh.h"
#include <Core/IFont.h>
#include <Core/Engine.h>


#include <sstream>


namespace TikiEngine
{
	namespace Resources
	{
		Model::Model(Engine* engine)
			: IModel(engine), material(0), indexBuffer(0), vertexBuffer(0), declaration(0), animationSpeed(1), rootBone(0)
		{
			constantBufferMatrices = new ConstantBuffer<SkinMatrices>(engine);

			Material* material = engine->content->LoadMaterial(L"os_skinning");
			this->SetMaterial(material);
		}

		Model::~Model()
		{
			for(UInt32 i = 0; i < animations.Count(); i++)
				SafeRelease(&animations[i]);

			for(UInt32 i = 0; i < meshes.Count(); i++)
				SafeRelease(&meshes[i]);

			SafeRelease(&declaration);
			SafeRelease(&material);
			SafeRelease(&indexBuffer);
			SafeRelease(&vertexBuffer);
			SafeDelete(&constantBufferMatrices);

			SafeRelease(&rootBone);
		}

		void Model::Initialize()
		{

			this->CopyIndexData();
			this->CopyVertexData();

		}


		void Model::AddAnimation(TikiAnimation* animation) //TODO ADD CURVES BLA
		{
			if(!this->animations.Contains(animation))
			{
				this->animations.Add(animation);
			}
			if(animations.Count() == 1)
				animationStack.Add(animation);
		}

		void* Model::GetNativeResource()
		{
			return 0;
		}

		bool Model::GetReady()
		{
			return (verticesList.Count() != 0 && indicesList.Count() != 0 && material != 0);
		}

		Material* Model::GetMaterial()
		{
			return material;
		}

		List<SkinningVertex>* Model::GetVertices()
		{
			return &verticesList;
		}

		List<UInt32>* Model::GetIndices()
		{
			return &indicesList;
		}
		
		void Model::SetMaterial(Material* material)
		{
			SafeRelease(&this->material);
			SafeAddRef(material, &this->material);

			SafeRelease(&declaration);

			if (material != 0 && material->GetReady())
			{
				declaration = new VertexDeclaration(engine, material->GetShader(), SkinningVertex::Declaration, SkinningVertex::DeclarationCount);
			}
					
			((Shader*)material->GetShader())->SetConstantBuffer("SkinMatrices", constantBufferMatrices->GetBuffer());
		}

		void Model::Draw(GameObject* gameObject, const DrawArgs& args)
		{
			if (!this->GetReady()) return;

			material->UpdateDrawArgs(args, gameObject);
			material->Apply();

			indexBuffer->Apply();
			vertexBuffer->Apply();

			DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			declaration->Apply();

			DllMain::Context->DrawIndexed(indicesList.Count(), 0, 0);

#if _DEBUG
			args.Graphics->DrawLine(Vector3(), Vector3(3.0f,0.0f,0.0f), Color::Red);
			args.Graphics->DrawLine(Vector3(), Vector3(0.0f,3.0f,0.0f), Color::Green);
			args.Graphics->DrawLine(Vector3(), Vector3(0.0f,0.0f,3.0f), Color::Blue);

			rootBone->Draw(args);
#endif
		}

		void Model::Update(const UpdateArgs& args)
		{
			if (!this->GetReady()) return;

			for(int i = 0; i < animationStack.Count(); i++)
			{
				animationStack[i]->Update(args.Time.ElapsedTime);
			}

			if(this->rootBone != 0)
				rootBone->Update(this->animationStack);

			SkinMatrices* matrices = constantBufferMatrices->Map();
			int matrixCount = this->constantBufferElements.Count();
			for(int i = 0; i < matrixCount; i++)
			{
				matrices->bones[i] = this->constantBufferElements[i]->ShiftMatrix();
			}
			constantBufferMatrices->Unmap();	

		}

		void Model::CopyVertexData()
		{
			verticesList.Clear();

			UInt32 i = 0;
			while (i < meshes.Count())
			{
				verticesList.AddRange(
					meshes[i]->verticesList.GetInternalData(),
					0,
					meshes[i]->verticesList.Count()
				);

				i++;
			}

			this->vertexBuffer = new StaticBuffer<D3D11_BIND_VERTEX_BUFFER>(engine, sizeof(SkinningVertex), verticesList.Count(), (void*)verticesList.GetInternalData());
		}

		void Model::CopyIndexData()
		{
			indicesList.Clear();

			UInt32 i = 0;
			UInt32 offset = 0;
			while (i < meshes.Count())
			{
				UInt32 a = 0;
				UInt32 c = meshes[i]->indicesList.Count();
				while (a < c)
				{
					indicesList.Add(
						meshes[i]->indicesList[a] + offset
					);

					a++;
				}

				offset += meshes[i]->verticesList.Count();
				i++;
			}
			this->indexBuffer = new StaticBuffer<D3D11_BIND_INDEX_BUFFER>(engine, sizeof(UINT), indicesList.Count(), (void*)indicesList.GetInternalData());
		}

		TikiBone* Model::GetRootBone()
		{
			return this->rootBone;
		}
		void Model::SetRootBone(TikiBone* bone)
		{
			if(this->rootBone != 0)
				SafeRelease(&rootBone);
			rootBone = bone;
			rootBone->AddRef();
		}

		void Model::SetConstantBufferIndices(List<TikiBone*>& list)
		{
			this->constantBufferElements = list;
		}

		void Model::loadFromStream(wcstring fileName, Stream* stream)
		{
			_CrtDbgBreak(); // nyi
			//FbxHelper* helper = new FbxHelper();

			//if(!DllMain::FBXLoader->GetScene(fileName, helper))
			//	_CrtDbgBreak();//FBXfile not found

			//this->scene = helper->GetScene();
			//this->SetRootBone(helper->GetRootBone());
			//this->AddAnimation(helper->GetAnimation());
			//this->SetConstantBufferIndices(helper->GetConstantBufferIndices());
			//this->SetMeshes(helper->GetMeshes());
			//if(!DllMain::FBXLoader->GetScene(fileName, &scene))
			//	_CrtDbgBreak(); //FBXfile not found

			Initialize();
		}

		void Model::saveToStream(wcstring fileName, Stream* stream)
		{

		}

		float Model::GetAnimationSpeed()
		{
			return this->animationSpeed;
		}

		void Model::SetAnimationSpeed(float speed)
		{
			this->animationSpeed = speed;
		}

		int Model::AnimationCount()
		{
			return this->animations.Count();
		}

		List<TikiMesh*> Model::GetMeshes()
		{
			return this->meshes;
		}

		void Model::SetMeshes(List<TikiMesh*>& meshes)
		{
			this->meshes = meshes;
		}

	}
}
