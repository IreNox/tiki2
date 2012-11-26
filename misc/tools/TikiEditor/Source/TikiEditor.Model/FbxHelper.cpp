
#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"

#include "FbxHelper.h"

namespace TikiEditor
{
	FbxHelper::FbxHelper()
		: scene(0), rootBone(0), animation(0)
	{

	}
	FbxHelper::~FbxHelper()
	{

	}

	FbxScene* FbxHelper::GetScene()
	{
		return this->scene;
	}

	void FbxHelper::SetScene(FbxScene* scene)
	{
		this->scene = scene;
		Initialize();
	}

	TikiBone* FbxHelper::GetRootBone()
	{
		return this->rootBone;
	}

	TikiAnimation* FbxHelper::GetAnimation()
	{
		return this->animation;
	}

	List<TikiBone*>& FbxHelper::GetConstantBufferIndices()
	{
		return this->constantBufferIndices;
	}
	List<TikiMesh*>& FbxHelper::GetMeshes()
	{
		return this->meshes;
	}

	void FbxHelper::Initialize()
	{
		FbxNode* root = this->scene->GetRootNode();
		RecursiveBone(root);
		BuildBoneHierachy(root);

		//int tmp = rootBone->Count();

		FlagBones();
		CleanBones(rootBone);

		InitializeAnimation();

		for(UInt32 i = 0; i < fbxNodes.Count(); i++)
			InitializeAnimationLayer(fbxNodes[i]);

		FindMeshes();
	}

	void FbxHelper::FindMeshes()
	{
		int meshCount = scene->GetSrcObjectCount<FbxMesh>();
		for(int i = 0; i < meshCount; i++)
			InitializeMesh(scene->GetSrcObject<FbxMesh>(i));
	}

	void FbxHelper::FlagBones()
	{
		if(rootBone == 0)
			return;

		int meshCount = scene->GetSrcObjectCount<FbxMesh>();
		for(int meshIndex = 0; meshIndex < meshCount; meshIndex++)
		{
			FbxMesh* mesh = scene->GetSrcObject<FbxMesh>(meshIndex);
				
			int skinCount =  mesh->GetDeformerCount(FbxDeformer::eSkin);
			for(int skinIndex = 0; skinIndex < skinCount; skinIndex++)
			{
				FbxSkin* skin = (FbxSkin*) mesh->GetDeformer(skinIndex, FbxDeformer::eSkin);

				int clustCount = skin->GetClusterCount();
				for(int clustIndex = 0; clustIndex < clustCount; clustIndex++)
				{
					FbxCluster* cluster = skin->GetCluster(clustIndex);
					if(!cluster->GetLink())
						continue;
					TikiBone* bone = rootBone->GetBoneByName(cluster->GetLink()->GetName());
					if(bone == 0)
						_CrtDbgBreak();
					bone->SetConstantBufferIndex(1);
				}
			}
		}
	}

	void FbxHelper::CleanBones(TikiBone* bone)
	{
		//void TikiBone::Clean()
		//{
		//	for(UINT i = 0; i < childs.Count(); i++)
		//	{
		//		childs[i]->Clean();

		//		if(childs[i]->childs.Count() == 0 && childs[i]->constantBufferIndex == -1)
		//		{
		//			childs[i]->Release();
		//			childs.RemoveAt(i);
		//		}
		//	}
		//}

		//void TikiBone::CreateMapping(List<TikiBone*>& list)
		//{
		//	if(constantBufferIndex != -1)
		//		list.Add(this);
		//	constantBufferIndex = list.Count() - 1;
		//	for(UInt32 i = 0; i < childs.Count(); i++)
		//		childs[i]->CreateMapping(list);
		//}

		if(bone == 0)
			return;

		if (bone->GetConstantBufferIndex() != -1)
		{
			constantBufferIndices.Add(bone);
			bone->SetConstantBufferIndex(constantBufferIndices.Count() - 1);
		}

		UInt32 i = 0;
		while (i < bone->GetChilds()->Count())
		{
			TikiBone* child = bone->GetChilds()->Get(i);

			this->CleanBones(child);

			if(child->GetChilds()->Count() == 0 && child->GetConstantBufferIndex() == -1)
			{
				child->Release();
				tikiBones.Remove(child);
				bone->GetChilds()->RemoveAt(i);
			}
			else
			{
				i++;
			}
		}
	}

	void FbxHelper::RecursiveBone(FbxNode* node)
	{
		fbxNodes.Add(node);
		for(int i = 0; i < node->GetChildCount(); i++)
			RecursiveBone(node->GetChild(i));
	}

	void FbxHelper::BuildBoneHierachy(FbxNode* node, TikiBone* parent)
	{
		TikiBone* bone = new TikiBone();
		bone->SetName(node->GetName());
		bone->SetBoneInitTransform(GlobalTransform(node));
		//bone->SetFbxNode(node); //TODO kicken

		this->tikiBones.Add(bone);

		if(parent == 0)
			rootBone = bone;
		else
		{
			parent->AddChild(bone);
			bone->SetParent(parent);
		}
		for(int i = 0; i < node->GetChildCount(); i++)
		{
			this->BuildBoneHierachy(node->GetChild(i), bone);
		}
	}

	void FbxHelper::InitializeMesh(FbxMesh* mesh)
	{
		TikiMesh* tiki = new TikiMesh();
		tiki->SetName(mesh->GetName());

		int vertexCount = mesh->GetControlPointsCount();

		List<Vector3> vertexList;
		GetGlobalVertices(vertexList, mesh);
		List<SkinningVertex> vertices;
		List<UInt32> indices;

		int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);
		tiki->SetDeformation(skinCount > 0);

		int maxBonesPerVertex = MaxBonesPerVertex(mesh);
#if _DEBUG
		if(tiki->UseDeformation() && maxBonesPerVertex > 4)
			_CrtDbgBreak();
#endif
			
		this->InitializeBufferData(vertexList, vertices, indices, mesh);

		this->InitializeSkinning(mesh, vertexList, vertices);

		tiki->SetSkinningVertexData(vertices);

		tiki->SetIndices(indices);

		meshes.Add(tiki);
	}

	void FbxHelper::InitializeBufferData(List<Vector3>& vertices, List<SkinningVertex>& buffer, List<UInt32>& indices, FbxMesh* mesh)
	{
		UInt32 counter = 0;
		Int32 polygonCount = mesh->GetPolygonCount();

		for(Int32 i = 0; i < polygonCount; i++)
		{
			Int32 verticesInPolygon = mesh->GetPolygonSize(i);
			if(verticesInPolygon != 3 && verticesInPolygon != 4)
				_CrtDbgBreak();

			UInt32 indicesArray[4];

			for(Int32 k = 0; k < verticesInPolygon; k++)
			{
				int index = mesh->GetPolygonVertex(i,k);

				Vector3 position = vertices[index];

				Vector2 uv;// = FbxVector2(0,0);
				int uvIndex = -1;

				if(mesh->GetElementUVCount() != 0)
				{
					uvIndex = mesh->GetElementUV(0)->GetIndexArray().GetAt(counter);
					uv = FBXConverter::Convert(mesh->GetElementUV(0)->GetDirectArray().GetAt(uvIndex));
				}

				Vector3 normals = FBXConverter::ConvertDrop(mesh->GetElementNormal(0)->GetDirectArray().GetAt(counter));

				SkinningVertex skin(
					position[0],position[1],position[2],
					uv[0],uv[1],
					normals[0],normals[1],normals[2]);

				indicesArray[k] = buffer.IndexOf(skin);
				if(indicesArray[k] == -1)
				{
					indicesArray[k] = buffer.Count();
					buffer.Add(skin);
				}
				counter++;
			}

			indices.Add(indicesArray[0]);
			indices.Add(indicesArray[1]);
			indices.Add(indicesArray[2]);

			if(verticesInPolygon == 4)
			{
				indices.Add(indicesArray[0]);
				indices.Add(indicesArray[2]);
				indices.Add(indicesArray[3]);
			}
		}
	}

	void FbxHelper::InitializeSkinning(FbxMesh* mesh, List<Vector3>& vertices, List<SkinningVertex>& buffer)
	{
		List<FbxCluster*> clusterList;
		GetSkinningCluster(mesh, clusterList);

		for(UInt32 i = 0; i < clusterList.Count(); i++)
		{
			FbxCluster* cluster = clusterList[i];

			TikiBone* bone = rootBone->GetBoneByName(cluster->GetLink()->GetName());
			if(bone == 0)
				_CrtDbgBreak(); // should find something

			FbxAMatrix bindTransform;
			cluster->GetTransformLinkMatrix(bindTransform);
			bone->SetBoneInitTransform(FBXConverter::ConvertTranspose(bindTransform));

			int vertexCount = cluster->GetControlPointIndicesCount();
			for(int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
			{
				int index = cluster->GetControlPointIndices()[vertexIndex];

				Vector3 position = vertices[index];

				for(UInt32 bufferIndex = 0; bufferIndex < buffer.Count(); bufferIndex++)
				{
					SkinningVertex& skin = buffer[bufferIndex];
					if(skin.Position[0] == position[0] && skin.Position[1] == position[1] && skin.Position[2] == position[2])
					{
						int vsIndex = 0;
						for(int k = 0; k < MAXBONESPERVERTEX; k++)
						{
							if(skin.BlendWeights[vsIndex] != -1)
								vsIndex++;
						}

						skin.BlendIndices[vsIndex] = (float)bone->GetConstantBufferIndex();
						skin.BlendWeights[vsIndex] = (float)cluster->GetControlPointWeights()[vertexIndex];
					}
				}
			}
		}
		for(UInt32 i = 0; i < buffer.Count(); i++)
		{
			SkinningVertex& skin = buffer[i];
			for(int k = 0; k < MAXBONESPERVERTEX; k++)
			{
				if(skin.BlendWeights[k] == -1)
					skin.BlendWeights[k] = 0;
			}
		}

	}

	void FbxHelper::GetSkinningCluster(FbxMesh* mesh, List<FbxCluster*>& clusterList)
	{
		int skinCount =  mesh->GetDeformerCount(FbxDeformer::eSkin);
		for(int skinIndex = 0; skinIndex < skinCount; skinIndex++)
		{
			FbxSkin *  skinDeformer = (FbxSkin*) mesh->GetDeformer(skinIndex, FbxDeformer::eSkin);

			int clusterCount = skinDeformer->GetClusterCount();
			for(int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
			{
				FbxCluster* cluster = skinDeformer->GetCluster(clusterIndex);
				if (!cluster->GetLink())
					continue;

				if(!clusterList.Contains(cluster))
					clusterList.Add(cluster);
			}
		}
	}

	void FbxHelper::GetGlobalVertices(List<Vector3>& list, FbxMesh* mesh)
	{
		int vertexCount = mesh->GetControlPointsCount();

		FbxVector4* vertexArray = new FbxVector4[vertexCount];
		memcpy(vertexArray, mesh->GetControlPoints(), vertexCount * sizeof(FbxVector4));

		for(int i = 0; i < vertexCount; i++)
		{
			vertexArray[i] = (static_cast<FbxMatrix>(mesh->GetNode()->EvaluateGlobalTransform(FBXSDK_TIME_INFINITE)).
				MultNormalize(vertexArray[i]));
			list.Add(FBXConverter::ConvertDrop(vertexArray[i]));
		}

		delete[]vertexArray;
		vertexArray = 0;
	}

	void FbxHelper::InitializeAnimation()
	{
		this->animation = new TikiAnimation();

		FbxAnimStack* stack = scene->GetSrcObject<FbxAnimStack>(0);
		if(stack == 0)
			return;
		animation->SetName(stack->GetName());

		for(int layerIndex = 0; layerIndex < stack->GetSrcObjectCount(); layerIndex++)
		{
			FbxAnimLayer* layer = stack->GetSrcObject<FbxAnimLayer>(layerIndex);
			for(UInt32 i = 0; i < fbxNodes.Count(); i++)
			{
				FbxAnimCurve* curve = fbxNodes[i]->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
				FillTimeStamp(curve);
				curve = fbxNodes[i]->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
				FillTimeStamp(curve);
				curve = fbxNodes[i]->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
				FillTimeStamp(curve);

				curve = fbxNodes[i]->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
				FillTimeStamp(curve);
				curve = fbxNodes[i]->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
				FillTimeStamp(curve);
				curve = fbxNodes[i]->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
				FillTimeStamp(curve);
			}
		}

		animation->GetTimeStamps().Sort();
		if (animation->GetTimeStamps().Count() == 0) animation->AddTimeStampKey(-1);

		UInt32 bsv = 1;
		while(bsv * 2 < animation->GetTimeStamps().Count())
			bsv *= 2;
		animation->SetBSV(bsv);
	}

	void FbxHelper::FillTimeStamp(FbxAnimCurve* curve)
	{
		if(curve == 0)
			return;

		for(int i = 0; i < curve->KeyGetCount(); i++)
		{
			animation->AddTimeStampKey(curve->KeyGetTime(i).GetSecondDouble());
		}
	}

	void FbxHelper::InitializeAnimationLayer(FbxNode* node)
	{
		TikiBone* bone = 0;
		for(UInt32 i = 0; i < tikiBones.Count(); i++)
		{
			if(node->GetName() == tikiBones[i]->GetName())
			{
				bone = tikiBones[i];
				break;
			}
		}
		if(bone == 0)
			return;

		TikiLayer layer;

		if(animation->GetTimeStamps().Count() == 1 && animation->GetTimeStamps()[0] == -1) // defaultValues
		{
			FbxAMatrix transform = node->EvaluateLocalTransform();

			layer.GetTranslation().Add(FBXConverter::ConvertDrop(transform.GetT()));
			layer.GetQuaternion().Add(FBXConverter::Convert(transform.GetQ()));
		}
		else
		{
			for(UInt32 i = 0; i < animation->GetTimeStamps().Count(); i++)
			{
				FbxTime time;
				time.SetSecondDouble(animation->GetTimeStamps()[i]);
				FbxAMatrix transform = node->EvaluateLocalTransform(time);

				layer.GetTranslation().Add(FBXConverter::ConvertDrop(transform.GetT()));
				layer.GetQuaternion().Add(FBXConverter::Convert(transform.GetQ()));
			}
		}

		bone->AddAnimation(this->animation, layer);
	}

	void FbxHelper::MergeAnimation(TikiAnimation* animation, TikiBone* destination, TikiBone* source)
	{
		TikiBone* bone = source->GetBoneByName(destination->GetName());
		if(bone == 0)
			_CrtDbgBreak();

		destination->AddAnimation(animation, bone->GetAnimationLayer(animation));

		for(UInt32 i = 0; i < destination->GetChilds()->Count(); i++)
			MergeAnimation(animation, destination->GetChilds()->Get(i), source);
	}


#pragma region NodeHelper
	Matrix FbxHelper::LocalTransform(FbxNode* node, FbxTime& time )
	{
		return FBXConverter::ConvertTranspose(node->EvaluateLocalTransform(time));
	}

	Matrix FbxHelper::GlobalTransform(FbxNode* node, FbxTime& time )
	{
		return FBXConverter::ConvertTranspose(node->EvaluateGlobalTransform(time));
	}
	int FbxHelper::MaxBonesPerVertex(FbxMesh* mesh)
	{
		bool hasSkin = mesh->GetDeformerCount(FbxDeformer::eSkin) > 0;

		if(!hasSkin)
			return -1;

		int* testData = new int[mesh->GetControlPointsCount()];
		for(int i = 0; i < mesh->GetControlPointsCount(); i++)
			testData[i] = 0;

		int skinCount =  mesh->GetDeformerCount(FbxDeformer::eSkin);
		for(int skinIndex = 0; skinIndex < skinCount; skinIndex++)
		{
			FbxSkin *  skinDeformer = (FbxSkin*) mesh->GetDeformer(skinIndex, FbxDeformer::eSkin);

			int clusterCount = skinDeformer->GetClusterCount();
			for(int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
			{
				FbxCluster* cluster = skinDeformer->GetCluster(clusterIndex);
				if (!cluster->GetLink())
					continue;
				int vertexCount = cluster->GetControlPointIndicesCount();
				for(int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
				{
					int index = cluster->GetControlPointIndices()[vertexIndex];

					if (index >= mesh->GetControlPointsCount())
						continue;

					testData[index]++;
				}

			}
		}

		int max = 0;
		for(int i = 0; i < mesh->GetControlPointsCount(); i++)
		{
			if(testData[i] > max)
				max = testData[i];

		}

		delete[] testData;
		return max;
	}
#pragma endregion

	List<const char*> FbxHelper::GetMeshNames(FbxScene* scene)
	{
		List<const char*> names;
		Int32 c = scene->GetSrcObjectCount<FbxMesh>();

		Int32 i = 0;
		while (i < c)
		{
			names.Add(
				scene->GetSrcObject<FbxMesh>(i)->GetNode()->GetName()
			);
			i++;
		}

		return names;	
	}

}