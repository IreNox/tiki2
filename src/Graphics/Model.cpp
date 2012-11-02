
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
		#pragma region Class
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
		#pragma endregion

		void Model::Initialize()
		{
			FbxAxisSystem directX(FbxAxisSystem::eDirectX);
			FbxAxisSystem sceneAxis = scene->GetGlobalSettings().GetAxisSystem();

			this->InitializeAnimationStack();
			this->SetCurrentAnimStack(0);

			FbxNode* root = scene->GetRootNode();
			this->InitializeNodeRecursive(root, currentTime, currentAnimLayer, this->GetGlobalPosition(root), NULL);

			this->CopyIndexData();
			this->CopyVertexData();
		}

		#pragma region Animation
		void Model::InitializeAnimationStack()
		{
			this->scene->FillAnimStackNameArray(this->animStackNameArray);
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

		float Model::GetAnimationSpeed()
		{
			return animationSpeed;
		}

		void Model::SetAnimationSpeed(float speed)
		{
			animationSpeed = speed;
		}
		#pragma endregion

		#pragma region Member - Get/Set
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
		#pragma endregion

		#pragma region Member - Draw/Update
		void Model::Draw(GameObject* gameObject, const DrawArgs& args)
		{
			if (!this->GetReady()) return;

			material->UpdateDrawArgs(args, gameObject);
			material->Apply();

			indexBuffer->Apply();
			vertexBuffer->Apply();

			//UINT offset = 0;
			//UINT stride = declaration->GetElementSize();

			//ID3D11Buffer* buffer = this->vertexBuffer->GetBuffer();
			////DllMain::Context->IASetVertexBuffers(
			////	0,
			////	1,
			////	&buffer,
			////	&stride,
			////	&offset
			////);

			////DllMain::Context->IASetIndexBuffer(
			////	this->indexBuffer->GetBuffer(),
			////	DXGI_FORMAT_R32_UINT,
			////	0
			////);

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

			if(timer > stopTime)
				timer = startTime;
			
			currentTime.SetSecondDouble(timer);

			UInt32 i = 0;
			while (i < meshes.Count())
			{
				meshes[i]->Update(currentTime, currentAnimLayer, NULL);
				i++;
			}

			SkinMatrices* matrices = constantBufferMatrices->Map();
			int matrixCount = meshes[0]->skinMatrices.Count();
			for(int i = 0; i < matrixCount; i++)
			{
				matrices->bones[i] = meshes[0]->skinMatrices[i].Transpose();
			}
			constantBufferMatrices->Unmap();		
		}
		#pragma endregion

		void Model::InitializeNodeRecursive(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer, FbxAMatrix& parentGlobalPosition, FbxPose* pose)
		{
			FbxAMatrix lGlobalPosition = GetGlobalPosition(node, time);

			//root has no NodeAttribute
			if(node->GetNodeAttribute())
			{
				FbxAMatrix lGeometryOffset = GetGeometry(node);
				FbxAMatrix lGlobalOffPosition = lGlobalPosition * lGeometryOffset;

				InitializeNode(node, time, animLayer, parentGlobalPosition, lGlobalOffPosition, pose);
			}
			for(int i = 0; i < node->GetChildCount(); i++)
			{
				InitializeNodeRecursive(node->GetChild(i), time, animLayer, lGlobalPosition, pose);
			}
		}
		void Model::InitializeNode(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer, FbxAMatrix& parentGlobalPosition, FbxAMatrix& globalPosition, FbxPose* pose)
		{
			if(node->GetNodeAttribute())
			{
				if(node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
				{
					InitializeMesh(node, time, animLayer, globalPosition, pose);
				}
				else if(node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
				{
					InitializeSkeleton(node, parentGlobalPosition, globalPosition);
				}
			}
		}
		void Model::InitializeMesh(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer,
			FbxAMatrix& globalPosition, FbxPose* pose)
		{
			if(node->GetMesh()->GetControlPointsCount() == 0)
				return;

			TikiMesh* tm = new TikiMesh(engine, node);
			tm->Initialize();

			meshes.Add(tm);
		}
		void Model::InitializeSkeleton(FbxNode* node, FbxAMatrix& parentGlobalPosition, FbxAMatrix& globalPosition)
		{
			FbxSkeleton* lSkeleton = (FbxSkeleton*) node->GetNodeAttribute();

			if(rootBone != 0)
				return;

			rootBone = new TikiBone(node);
			rootBone->Initialize();
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

			//this->vertexBuffer->FillBuffer(verticesList.GetInternalData(), verticesList.Count());
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
			//this->indexBuffer->FillBuffer(indicesList.GetInternalData(), indicesList.Count());
			this->indexBuffer = new StaticBuffer<D3D11_BIND_INDEX_BUFFER>(engine, sizeof(UINT), indicesList.Count(), (void*)indicesList.GetInternalData());

		}


		#pragma region Math
		FbxAMatrix& Model::GetGlobalPosition(FbxNode* node, FbxTime pTime)
		{
			return node->EvaluateGlobalTransform(pTime);
		}

		FbxAMatrix Model::GetGeometry(FbxNode* node)
		{
			const FbxVector4 lT = node->GetGeometricTranslation(FbxNode::eSourcePivot);
			const FbxVector4 lR = node->GetGeometricRotation(FbxNode::eSourcePivot);
			const FbxVector4 lS = node->GetGeometricScaling(FbxNode::eSourcePivot);

			return FbxAMatrix(lT, lR, lS);
		}
		#pragma endregion

		#pragma region Protected Member - Load/Save
		void Model::loadFromStream(wcstring fileName, Stream* stream)
		{
			if(!DllMain::FBXLoader->GetScene(fileName, &scene))
				throw L"FBXfile not found";

			Initialize();
		}

		void Model::saveToStream(wcstring fileName, Stream* stream)
		{

		}
		#pragma endregion
	}
}
