
#include "Graphics/Model.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"
#include "Core/IContentManager.h"
#include "Core/LibraryManager.h"
#include "Core/ISpriteBatch.h"

#include "Graphics/DllMain.h"
#include "Graphics/FbxLoader.h"
#include "Graphics/TikiMesh.h"
#include <Core/IFont.h>
#include <Core/Engine.h>
#include "Graphics/FbxLoader.h"

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
			FbxArrayDelete(animStackNameArray);
			this->scene->Destroy();

			SafeRelease(&declaration);
			SafeRelease(&material);
			SafeRelease(&indexBuffer);
			SafeRelease(&vertexBuffer);
			SafeDelete(&constantBufferMatrices);

			SafeRelease(&rootBone);
		}

		void Model::Initialize()
		{

			//this->InitializeAnimationStack();
			//this->SetCurrentAnimStack(0);

			//this->CreateBoneHierachy(scene->GetRootNode());
			this->InitializeMeshes();

			this->FlagBones();
			this->CleanBones();
			this->MapBones();

			this->CopyIndexData();
			this->CopyVertexData();

			//this->InitializeAnimation();
		}

		void Model::InitializeMeshes()
		{
			int meshCount = this->scene->GetSrcObjectCount<FbxMesh>();
#if _DEBUG
			if(!meshCount)
				_CrtDbgBreak(); //no meshes -> not supported
#endif
			for(int meshIndex = 0; meshIndex < meshCount; meshIndex ++)
			{
				FbxMesh* mesh = this->scene->GetSrcObject<FbxMesh>(meshIndex);

				TikiMesh* tm = new TikiMesh(engine, mesh->GetNode());
				tm->Initialize();
				meshes.Add(tm);
			}
		}

		void Model::InitializeAnimation()
		{
			if(this->rootBone == 0)
				return;
			for(int i = 0; i < this->animations.Count(); i++)
				rootBone->InitializeAnimation(animations[i]);
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

		void Model::FlagBones()
		{
			int meshCount = meshes.Count();
			for(int meshIndex = 0; meshIndex < meshCount; meshIndex ++)
				meshes[meshIndex]->FlagBones(*rootBone);
		}

		void Model::CleanBones()
		{
			rootBone->Clean();
			rootBone->CreateMapping(this->constantBufferElements);
		}

		void Model::MapBones()
		{
			int meshCount = meshes.Count();
			for(int meshIndex = 0; meshIndex < meshCount; meshIndex ++)
				meshes[meshIndex]->MapBones(*rootBone);
		}

		void Model::CreateBoneHierachy(FbxNode* node)
		{
			_CrtDbgBreak();
			//if(rootBone != 0)
			//	return;

			//rootBone = new TikiBone(node);
			//rootBone->AddRef();
			//rootBone->Initialize();
		}

		void Model::InitializeAnimationStack()
		{
			_CrtDbgBreak();
			//this->scene->FillAnimStackNameArray(this->animStackNameArray);

			//int animationStackcount = this->scene->GetSrcObjectCount<FbxAnimStack>();
			//for(int i = 0; i < animationStackcount; i++)
			//{
			//	FbxAnimStack* stack = this->scene->GetSrcObject<FbxAnimStack>(i);
			//	int animLayerCount = stack->GetSrcObjectCount<FbxAnimLayer>();
			//	for(int k = 0; k < animLayerCount; k++)
			//	{
			//		TikiAnimation* animation = new TikiAnimation(stack->GetSrcObject<FbxAnimLayer>(k));
			//		animation->AddRef();
			//		this->animations.Add(animation);
			//	}
			//}
		}

		void Model::SetCurrentAnimStack(int pIndex)
		{
			_CrtDbgBreak();
			//int animationCount = animations.Count();

			//if(pIndex < 0 || pIndex >= animationCount)
			//	return;

			//TikiAnimation* animation = animations.Get(pIndex);

			//FbxAnimStack* stack = FbxAnimStack::Create(this->scene, animation->GetName());
			//animation->Layer()->Weight = 100;
			//stack->AddMember(animation->Layer());

			//this->scene->GetEvaluator()->SetContext(stack);

		}

		void* Model::GetNativeResource()
		{
			return scene;
		}

		bool Model::GetReady()
		{
			return (scene != 0 && material != 0);
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

		void Model::loadFromStream(wcstring fileName, Stream* stream)
		{
			FbxHelper* helper = new FbxHelper();

			if(!DllMain::FBXLoader->GetScene(fileName, helper))
				_CrtDbgBreak();//FBXfile not found

			this->scene = helper->GetScene();
			this->SetRootBone(helper->GetRootBone());
			this->AddAnimation(helper->GetAnimation());

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

	}
}
