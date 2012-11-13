
#include "Graphics/Model.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"
#include "Core/IContentManager.h"

#include "Graphics/DllMain.h"
#include "Graphics/FbxLoader.h"
#include "Graphics/Deformer.h"
#include "Graphics/TikiMesh.h"


namespace TikiEngine
{
	namespace Resources
	{
		Model::Model(Engine* engine)
			: IModel(engine), material(0), indexBuffer(0), vertexBuffer(0), declaration(0), animationSpeed(1), rootBone(0)
		{
			constantBufferMatrices = new ConstantBuffer<SkinMatrices>(engine);

			Material* material = engine->content->LoadMaterial(L"os_skinning");
			((Shader*)material->GetShader())->SetConstantBuffer("SkinMatrices", constantBufferMatrices->GetBuffer());
			this->SetMaterial(material);
		}

		Model::~Model()
		{
			for(UInt32 i = 0; i < animations.Count(); i++)
			{
				SafeRelease(&animations[i]);
			}

			for(UInt32 i = 0; i < meshes.Count(); i++)
			{
				SafeRelease(&meshes[i]);
			}
			FbxArrayDelete(animStackNameArray);
			this->scene->Destroy();

			SafeRelease(&declaration);
			SafeRelease(&material);
			SafeRelease(&indexBuffer);
			SafeRelease(&vertexBuffer);
			SafeDelete(&constantBufferMatrices);

			if(rootBone != 0)
				SafeRelease(&rootBone);
		}

		void Model::Initialize()
		{

			this->InitializeAnimationStack();
			this->SetCurrentAnimStack(0);

			this->CreateBoneHierachy(scene->GetRootNode());
			this->InitializeMeshes();

			this->FlagBones();
			this->CleanBones();
			this->MapBones();

			this->CopyIndexData();
			this->CopyVertexData();

			this->InitializeAnimation();
			

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

		void Model::InitializeBoneMapping()
		{
			if(rootBone == 0)
				return;
			for(int i = 0; i < meshes.Count(); i++)
				meshes[0]->InitializeBones(*rootBone);
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
			if(rootBone != 0)
				return;

			rootBone = new TikiBone(node);
			rootBone->AddRef();
			rootBone->Initialize();
		}

		void Model::InitializeAnimationStack()
		{
			this->scene->FillAnimStackNameArray(this->animStackNameArray);

			int animationStackcount = this->scene->GetSrcObjectCount<FbxAnimStack>();
			for(int i = 0; i < animationStackcount; i++)
			{
				TikiAnimation* animation = new TikiAnimation(this->scene->GetSrcObject<FbxAnimStack>(i));
				this->animations.Add(animation);
			}
		}

		bool Model::SetCurrentAnimStack(int pIndex)
		{
			const int lAnimStackCount = animStackNameArray.GetCount();
			if (!lAnimStackCount || pIndex >= lAnimStackCount)
			{
				return false;
			}
			

			FbxAnimStack* lCurrentAnimationStack = this->scene->FindMember<FbxAnimStack>(animStackNameArray[pIndex]->Buffer());
			//// select the base layer from the animation stack
			if (lCurrentAnimationStack == NULL)
			{
				// this is a problem. The anim stack should be found in the scene!
				return false;
			}

			currentAnimLayer = lCurrentAnimationStack->GetMember<FbxAnimLayer>();
			scene->GetEvaluator()->SetContext(lCurrentAnimationStack);

			FbxTakeInfo* lCurrentTakeInfo = scene->GetTakeInfo(*(animStackNameArray[pIndex]));
			if (lCurrentTakeInfo)
			{
				start = lCurrentTakeInfo->mLocalTimeSpan.GetStart();
				stop = lCurrentTakeInfo->mLocalTimeSpan.GetStop();
			}
			else
			{
				// Take the time line value
				FbxTimeSpan lTimeLineTimeSpan;
				scene->GetGlobalSettings().GetTimelineDefaultTimeSpan(lTimeLineTimeSpan);

				start = lTimeLineTimeSpan.GetStart();
				stop  = lTimeLineTimeSpan.GetStop();
			}

			frameTime.SetTime(0, 0, 0, 1, 0, scene->GetGlobalSettings().GetTimeMode());

			startTime = start.GetSecondDouble();
			stopTime = stop.GetSecondDouble();
			timer = startTime;


			// move to beginning
			currentTime = start;


			return true;
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

			args.Graphics->DrawLine(Vector3(), Vector3(3.0f,0.0f,0.0f), Color::Red);
			args.Graphics->DrawLine(Vector3(), Vector3(0.0f,3.0f,0.0f), Color::Green);
			args.Graphics->DrawLine(Vector3(), Vector3(0.0f,0.0f,3.0f), Color::Blue);
		}

		void Model::Update(const UpdateArgs& args)
		{
			if (!this->GetReady()) return;

			FbxNode* root = this->scene->GetRootNode();

			timer += args.Time.ElapsedTime;

			if(timer >= stopTime)
				timer -= stopTime - startTime;
			
			if(this->rootBone != 0)
				rootBone->Update(timer);


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

		void Model::loadFromStream(wcstring fileName, Stream* stream)
		{
			if(!DllMain::FBXLoader->GetScene(fileName, &scene))
				throw L"FBXfile not found";

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

	}
}
