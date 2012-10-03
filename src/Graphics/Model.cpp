
#include "Graphics/Model.h"
#include "Core/TypeGlobals.h"

#include "Graphics/DllMain.h"
#include "Graphics/FbxLoader.h"
#include "Graphics/Deformer.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Model::Model(Engine* engine)
			: IModel(engine), indices(0), indicesCount(0), vertices(0), verticesSize(0)
		{
		}

		Model::~Model()
		{
			SafeDelete(&indices);
			SafeDelete(&vertices);
		}
		#pragma endregion

		void Model::Initialize()
		{
			this->InitializeAnimationStack();
			this->SetCurrentAnimStack(0);

			FbxNode * root = this->scene->GetRootNode();
			this->HandleNodeRecursive(
				root,
				FBXSDK_TIME_INFINITE,
				currentAnimLayer,
				GetGlobalPosition(root),
				NULL);
			FillData();
		}
		void Model::FillData()
		{
			int bla = this->verticesList.Count();
			int bla2 = this->indicesList.Count();
			this->SetVertexData(this->verticesList.ToArray(), this->verticesList.Count() * sizeof(DefaultVertex));
			this->SetIndexData(this->indicesList.ToArray(), this->indicesList.Count());
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

			return true;
		}
		#pragma endregion

		#pragma region Member

		void Model::SetIndexData(UInt32* indices, UInt32 count)
		{
			SafeDelete(&this->indices);
			this->indices = new UInt32[count];
			this->indicesCount = count;

			memcpy(
				this->indices,
				indices,
				count * sizeof(UInt32)
			);
		}

		bool Model::GetIndexData(UInt32** indices, UInt32* count)
		{
			*indices = this->indices;
			*count = indicesCount;

			return (indices != 0);
		}

		void Model::SetVertexData(void* vertices, UInt32 size)
		{
			SafeDelete(&this->vertices);

			this->vertices = new Byte[size];
			this->verticesSize = size;
			memcpy(this->vertices, vertices, size);
		}

		bool Model::GetVertexData(void** vertices, UInt32* size)
		{
			*vertices = this->vertices;
			*size = this->verticesSize;

			return (vertices != 0);
		}


		void* Model::GetNativeResource()
		{
			return NULL;
		}

		bool Model::GetReady()
		{
			return (indices != 0 && vertices != 0);
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

			const int vertexCount = mesh->GetControlPointsCount();

			if(vertexCount == 0)
				return;

			const bool hasShape = mesh->GetShapeCount() > 0;
			const bool hasSkin = mesh->GetDeformerCount(FbxDeformer::eSkin) > 0;
			const bool hasDeformation = hasShape || hasSkin;

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

			UInt32 indicesOffset = this->indicesList.Count();

			UInt32 counter = 0;

			for(UInt32 i = 0; i < mesh->GetPolygonVertexCount();i++)
			{
				Int32 verticesInPolygon = mesh->GetPolygonSize(i);

				indicesList.Add(indicesOffset + counter);
				indicesList.Add(indicesOffset + counter + 1);
				indicesList.Add(indicesOffset + counter + 2);

				if(verticesInPolygon == 4)
				{
					indicesList.Add(indicesOffset + counter);
					indicesList.Add(indicesOffset + counter + 2);
					indicesList.Add(indicesOffset + counter + 3);
				}
				for(Int32 k = 0; k < verticesInPolygon; k++)
				{
					int index = mesh->GetPolygonVertex(i,k);

					FbxVector4 position = vertexArray[index];

					FbxVector2 uv = FbxVector2(0,0);
					if(mesh->GetElementUVCount() != 0)
					{
						int uvIndex = mesh->GetElementUV(0)->GetIndexArray().GetAt(counter);
						uv = mesh->GetElementUV(0)->GetDirectArray().GetAt(uvIndex);
					}
					FbxVector4 normals = mesh->GetElementNormal(0)->GetDirectArray().GetAt(counter);
					FbxVector4 binormal = FbxVector4();
					FbxVector4 tangent = FbxVector4();

					DefaultVertex default = {
						(float)position[0],
						(float)position[1],
						(float)position[2],
						(float)uv[0],
						(float)uv[1],
						(float)normals[0],
						(float)normals[1],
						(float)normals[2],
						(float)binormal[0],
						(float)binormal[1],
						(float)binormal[2],
						(float)tangent[0],
						(float)tangent[1],
						(float)tangent[2]

					};	
					this->verticesList.Add(default);
					counter++;
				}
			}
		}


		#pragma region Math
		FbxAMatrix& Model::GetGlobalPosition(FbxNode* node, FbxTime pTime)
		{
			return node->EvaluateGlobalTransform(pTime);
		}
		FbxAMatrix& Model::GetGeometry(FbxNode* node)
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
