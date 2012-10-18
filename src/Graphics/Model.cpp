
#include "Graphics/Model.h"
#include "Core/TypeGlobals.h"

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
			: IModel(engine), material(0), indexBuffer(0), vertexBuffer(0), declaration(0)
		{
			indexBuffer = new DynamicBuffer<UInt32, D3D11_BIND_INDEX_BUFFER>(engine);
			vertexBuffer = new DynamicBuffer<DefaultVertex, D3D11_BIND_VERTEX_BUFFER>(engine);
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

			
		}

		#pragma endregion

		void Model::Initialize()
		{
			this->InitializeAnimationStack();
			this->SetCurrentAnimStack(1);

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

			// move to beginning
			currentTime = start;

			return true;
		}
		#pragma endregion

		#pragma region Member - Get/Set
		void* Model::GetNativeResource()
		{
			return scene;
		}

		bool Model::GetReady()
		{
			return (scene != 0);
		}

		Material* Model::GetMaterial()
		{
			return material;
		}

    List<DefaultVertex>* Model::GetVertices()
    {
      return &verticesList;
    }

    List<UInt32>* Model::GetIndices()
    {
      return &indicesList;
    }



		void Model::SetMaterial(Material* material)
		{
			SafeAddRef(material, &this->material);

			SafeRelease(&declaration);

			if (material != 0 && material->GetReady())
			{
				declaration = new VertexDeclaration(engine, material->GetShader(), DefaultVertex::Declaration, DefaultVertex::DeclarationCount);
			}
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void Model::Draw(GameObject* gameObject, const DrawArgs& args)
		{
			if (!this->GetReady()) return;

			material->UpdateDrawArgs(args, gameObject);
			material->Apply();

			UINT offset = 0;
			UINT stride = declaration->GetElementSize();

			ID3D11Buffer* buffer = this->vertexBuffer->GetBuffer();
			DllMain::Context->IASetVertexBuffers(
				0,
				1,
				&buffer,
				&stride,
				&offset
			);

			DllMain::Context->IASetIndexBuffer(
				this->indexBuffer->GetBuffer(),
				DXGI_FORMAT_R32_UINT,
				0
			);

			DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			declaration->Apply();

			DllMain::Context->DrawIndexed(indicesList.Count(), 0, 0);
		}

		void Model::Update(const UpdateArgs& args)
		{
			if (!this->GetReady()) return;

			FbxNode* root = this->scene->GetRootNode();

			currentTime += frameTime;

			if (currentTime > stop)
			{
				currentTime = start;
			}

			UInt32 i = 0;
			while (i < meshes.Count())
			{
				meshes[i]->Update(currentTime, currentAnimLayer, NULL);
				i++;
			}

			this->CopyVertexData();			
		}
		#pragma endregion

		void Model::HandleNodeRecursive(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer, FbxAMatrix& parentGlobalPosition, FbxPose* pose)
		{
			FbxAMatrix lGlobalPosition = GetGlobalPosition(node, time);

			//root has no NodeAttribute
			if(node->GetNodeAttribute())
			{
				FbxAMatrix lGeometryOffset = GetGeometry(node);
				FbxAMatrix lGlobalOffPosition = lGlobalPosition * lGeometryOffset;

				HandleNode(node, time, animLayer, parentGlobalPosition, lGlobalOffPosition, pose);
			}
			for(int i = 0; i < node->GetChildCount(); i++)
			{
				HandleNodeRecursive(node->GetChild(i), time, animLayer, lGlobalPosition, pose);
			}
		}

		void Model::HandleNode(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer, FbxAMatrix& parentGlobalPosition, FbxAMatrix& globalPosition, FbxPose* pose)
		{
			if(node->GetNodeAttribute())
			{
				if(node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
				{
					HandleMesh(node, time, animLayer, globalPosition, pose);
				}
				else if(node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
				{
					HandleSkeleton(node, parentGlobalPosition, globalPosition);
				}
			}
		}
		
		void Model::HandleSkeleton(FbxNode* node, FbxAMatrix& parentGlobalPosition, FbxAMatrix& globalPosition)
		{
			//FbxSkeleton* lSkeleton = (FbxSkeleton*) pNode->GetNodeAttribute();

			////Only draw the skeleton if it's a limb node and if 
			////the parent also has an attribute of type skeleton.
			//if (lSkeleton->GetSkeletonType() == FbxSkeleton::eLimbNode &&
			//	pNode->GetParent() &&
			//	pNode->GetParent()->GetNodeAttribute() &&
			//	pNode->GetParent()->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
			//{

			//	this->skeletonList.Add(pParentGlobalPosition.GetT());
			//	this->skeletonList.Add(pGlobalPosition.GetT());
			//}
		}
		
		void Model::HandleMesh(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer,
			FbxAMatrix& globalPosition, FbxPose* pose)
		{
			FbxMesh* mesh = node->GetMesh();

			int vertexCount = mesh->GetControlPointsCount();

			if(vertexCount == 0)
				return;

			TikiMesh tm = TikiMesh(engine, node);
			tm.Initialize();

			bool hasShape = mesh->GetShapeCount() > 0;
			bool hasSkin = mesh->GetDeformerCount(FbxDeformer::eSkin) > 0;
			bool hasDeformation = hasShape || hasSkin;

			FbxVector4* vertexArray = new FbxVector4[vertexCount];
			memcpy(vertexArray, mesh->GetControlPoints(), vertexCount * sizeof(FbxVector4));
			
			if(hasDeformation)
			{
				if(hasShape)
				{
					Deformer::ComputeShapeDeformation(mesh, time, animLayer, vertexArray);
				}

				const int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);
				int clusterCount = 0;
				for(int i = 0; i < skinCount; i++)
				{
					clusterCount += ((FbxSkin *)(mesh->GetDeformer(i, FbxDeformer::eSkin)))->GetClusterCount();
				}
				if(clusterCount)
				{
					Deformer::ComputeSkinDeformation(globalPosition, mesh, time, vertexArray, pose);
				}
			}

			for(int i = 0; i < vertexCount; i++)
			{
				vertexArray[i] = (static_cast<FbxMatrix>(globalPosition).MultNormalize(vertexArray[i]));
			}

			if(!this->GetReady())
			{
				UInt32 indicesOffset = this->verticesList.Count();

				UInt32 counter = 0;

				for(Int32 i = 0; i < mesh->GetPolygonVertexCount();i++)
				{
					Int32 verticesInPolygon = mesh->GetPolygonSize(i);

					UInt32 indicesArray[4];

					for(Int32 k = 0; k < verticesInPolygon; k++)
					{
						int index = mesh->GetPolygonVertex(i,k);

						FbxVector4 position = vertexArray[index];

						FbxVector2 uv = FbxVector2(0,0);
						int uvIndex = -1;

						if(mesh->GetElementUVCount() != 0)
						{
							uvIndex = mesh->GetElementUV(0)->GetIndexArray().GetAt(counter);
							uv = mesh->GetElementUV(0)->GetDirectArray().GetAt(uvIndex);
						}

						FbxVector4 normals = mesh->GetElementNormal(0)->GetDirectArray().GetAt(counter);

						int blub = mesh->GetElementTangentCount();
						FbxVector4 binormal = FbxVector4();
						FbxVector4 tangent = FbxVector4();

						DefaultVertex default = {
							(float)position[0],(float)position[1],(float)position[2],
							(float)uv[0],(float)uv[1],
							(float)normals[0],(float)normals[1],(float)normals[2],
							(float)binormal[0],(float)binormal[1],(float)binormal[2],
							(float)tangent[0],(float)tangent[1],(float)tangent[2]
						};	

						indicesArray[k] = verticesList.IndexOf(default);
						if(indicesArray[k] == -1)
						{
							//UpdateStructure us = 
							//{
							//	i,k,uvIndex,counter
							//};
							//this->updateStructure.Add(us);
							indicesArray[k] = verticesList.Count();
							verticesList.Add(default);
						}
					}

					indicesList.Add(indicesArray[0]);
					indicesList.Add(indicesArray[1]);
					indicesList.Add(indicesArray[2]);

					if(verticesInPolygon == 4)
					{
						indicesList.Add(indicesArray[0]);
						indicesList.Add(indicesArray[2]);
						indicesList.Add(indicesArray[3]);
					}
				}
			}
			else
			{
				
			}
		}

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
					//Ini(node, parentGlobalPosition, globalPosition);
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

			DefaultVertex* vertexData = vertexBuffer->Map(verticesList.Count());
			memcpy(vertexData, verticesList.GetInternalData(), sizeof(DefaultVertex) * verticesList.Count());
			vertexBuffer->Unmap();
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

			UInt32* indexData = indexBuffer->Map(indicesList.Count());
			memcpy(indexData, indicesList.GetInternalData(), sizeof(UInt32) * indicesList.Count());
			indexBuffer->Unmap();
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

			//DllMain::FBXLoader->LoadFile(
			//	fileName,
			//	&indices,
			//	&indicesCount,
			//	&vertices,
			//	&verticesSize,
			//	&scene
			//);
		}

		void Model::saveToStream(wcstring fileName, Stream* stream)
		{

		}
		#pragma endregion
	}
}
