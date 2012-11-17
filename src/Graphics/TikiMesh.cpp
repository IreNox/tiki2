#include "Graphics/TikiMesh.h"
#include "Graphics/FBXConverter.h"

namespace TikiEngine
{
	namespace Resources
	{
		TikiMesh::TikiMesh(Engine* engine, FbxNode* node)
			:engine(engine),
			node(node)
		{

		}
		TikiMesh::~TikiMesh()
		{
			//node->Destroy();
		}

		bool TikiMesh::Initialize()
		{
			FbxMesh* mesh = node->GetMesh();

			int vertexCount = mesh->GetControlPointsCount();

			FbxVector4* vertexArray = new FbxVector4[vertexCount];
			memcpy(vertexArray, mesh->GetControlPoints(), vertexCount * sizeof(FbxVector4));

			for(int i = 0; i < vertexCount; i++)
			{
				vertexArray[i] = (static_cast<FbxMatrix>(node->EvaluateGlobalTransform(FBXSDK_TIME_INFINITE)).
					MultNormalize(vertexArray[i]));
			}


			int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);
			this->hasDeformation = skinCount > 0;

			int maxBonesPerVertex = MaxBonesPerVertex();
#if _DEBUG
			if(hasDeformation && maxBonesPerVertex > 4)
				_CrtDbgBreak();
#endif

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

					FbxVector4 position = vertexArray[index];

					FbxVector2 uv = FbxVector2(0,0);
					int uvIndex = -1;

					if(mesh->GetElementUVCount() != 0)
					{
						uvIndex = mesh->GetElementUV(0)->GetIndexArray().GetAt(counter);
						uv = mesh->GetElementUV(0)->GetDirectArray().GetAt(uvIndex);
					}

					FbxVector4 normals = mesh->GetElementNormal(0)->GetDirectArray().GetAt(counter);

					SkinningVertex skin = {
						(float)position[0],(float)position[1],(float)position[2],
						(float)uv[0],(float)uv[1],
						(float)normals[0],(float)normals[1],(float)normals[2],
						0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f
					};

					indicesArray[k] = verticesList.IndexOf(skin);
					if(indicesArray[k] == -1)
					{
						UpdateStructure us = {index, uvIndex, counter, Vector4(-1), Vector4(0.0f)};
						this->updateStructure.Add(us);
						indicesArray[k] = verticesList.Count();
						verticesList.Add(skin);
					}
					counter++;
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
			delete[]vertexArray;
			vertexArray = 0;

			//this->InitializeGPUSkinning();
			//this->UpdateVertexBuffer();

			return true;
		}
	
		void TikiMesh::InitializeGPUSkinning()
		{
			FbxMesh* mesh = this->node->GetMesh();
			bool hasSkin = mesh->GetDeformerCount(FbxDeformer::eSkin) > 0;

			//if(!hasSkin)
			//	return;

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

						int updatestructureCount = updateStructure.Count();
						for(int updateIndex = 0; updateIndex < updatestructureCount; updateIndex++)
						{
							if(updateStructure[updateIndex].VertexIndex == index)
							{
								UpdateStructure us = updateStructure[updateIndex];

								int vsIndex = 0;
								while(us.Weights.arr[vsIndex] != -1)
									vsIndex++;

								us.Indices.arr[vsIndex] = (float)clusterIndex;
								us.Weights.arr[vsIndex] = (float)cluster->GetControlPointWeights()[vertexIndex];
								updateStructure.Set(updateIndex,us);
							}
						}
					}
				}
			}

			int updateCount = updateStructure.Count();
			for(int updateIndex = 0; updateIndex < updateCount; updateIndex++)
			{
				UpdateStructure us = updateStructure[updateIndex];
				for(int i = 0; i < 4; i++)
				{
					if(us.Weights.arr[i] == -1)
						us.Weights.arr[i] = 0;
				}
				updateStructure.Set(updateIndex, us);
			}
		}

		void TikiMesh::InitializeBones(TikiBone& rootBone)
		{
			this->bones.Clear();

			FbxMesh* mesh = node->GetMesh();

			int skinCount =  mesh->GetDeformerCount(FbxDeformer::eSkin);
			for(int skinIndex = 0; skinIndex < skinCount; skinIndex++)
			{
				FbxSkin *  skin = (FbxSkin*) mesh->GetDeformer(skinIndex, FbxDeformer::eSkin);

				int clusterCount = skin->GetClusterCount();
				for(int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
				{
					FbxCluster* cluster = skin->GetCluster(clusterIndex);

					if(!cluster->GetLink())
						continue;

					TikiBone* bone = rootBone.GetBoneByName(cluster->GetLink()->GetName());
					FbxAMatrix bindPose;
					cluster->GetTransformLinkMatrix(bindPose);
					bone->SetBind(bindPose);

					if(bone != 0)
						bones.Add(bone);
#if _DEBUG
					else
					{
						const char* name = cluster->GetLink()->GetName();
						_CrtDbgBreak();
					}
#endif
				}
			}
		}

		void TikiMesh::FlagBones(TikiBone& rootBone)
		{
			if(!hasDeformation)
				return;

			FbxMesh* mesh = this->node->GetMesh();

			if(mesh->GetDeformerCount(FbxDeformer::eSkin) != 1) // zu viele skins - nicht supported
				_CrtDbgBreak();

			FbxSkin *  skinDeformer = (FbxSkin*) mesh->GetDeformer(0, FbxDeformer::eSkin);

			int clusterCount = skinDeformer->GetClusterCount();
			for(int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
			{
				FbxCluster* cluster = skinDeformer->GetCluster(clusterIndex);
				if (!cluster->GetLink())
					continue;

				TikiBone* bone = rootBone.GetBoneByName(cluster->GetLink()->GetName());
				if(bone == 0)
					_CrtDbgBreak();
				bone->SetConstantBufferIndex(1);
			}
		}

		void TikiMesh::MapBones(TikiBone& rootBone)
		{
			if(!hasDeformation)
				return;

			FbxMesh* mesh = this->node->GetMesh();

			if(mesh->GetDeformerCount(FbxDeformer::eSkin) != 1) // zu viele skins - nicht supported
				_CrtDbgBreak();

			List<FbxCluster*> clusterz;

			FbxSkin *  skinDeformer = (FbxSkin*) mesh->GetDeformer(0, FbxDeformer::eSkin);

			int clusterCount = skinDeformer->GetClusterCount();
			for(int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
			{
				FbxCluster* cluster = skinDeformer->GetCluster(clusterIndex);
				if (!cluster->GetLink())
					continue;

				TikiBone* bone = rootBone.GetBoneByName(cluster->GetLink()->GetName());
				if(bone == 0)
					_CrtDbgBreak();

				FbxAMatrix bindPose;
				cluster->GetTransformLinkMatrix(bindPose);
				bone->SetBind(bindPose);

				int vertexCount = cluster->GetControlPointIndicesCount();
				for(int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
				{
					int index = cluster->GetControlPointIndices()[vertexIndex];

					if (index >= mesh->GetControlPointsCount())
						continue;

					int updatestructureCount = updateStructure.Count();
					for(int updateIndex = 0; updateIndex < updatestructureCount; updateIndex++)
					{
						if(updateStructure[updateIndex].VertexIndex == index)
						{
							UpdateStructure us = updateStructure[updateIndex];

							int vsIndex = 0;
							while(us.Weights.arr[vsIndex] != -1)
								vsIndex++;

							us.Indices.arr[vsIndex] = (float)bone->GetConstantBufferIndex();
							us.Weights.arr[vsIndex] = (float)cluster->GetControlPointWeights()[vertexIndex];
							updateStructure.Set(updateIndex,us);
						}
					}
				}
			}
			int updateCount = updateStructure.Count();
			for(int updateIndex = 0; updateIndex < updateCount; updateIndex++)
			{
				UpdateStructure us = updateStructure[updateIndex];
				for(int i = 0; i < 4; i++)
				{
					if(us.Weights.arr[i] == -1)
						us.Weights.arr[i] = 0;
				}
				updateStructure.Set(updateIndex, us);
			}
			this->UpdateVertexBuffer();
		}

		void TikiMesh::UpdateVertexBuffer()
		{
			FbxMesh* mesh = node->GetMesh();

			int vertexCount = mesh->GetControlPointsCount();

			FbxVector4* vertexArray = new FbxVector4[vertexCount];
			memcpy(vertexArray, mesh->GetControlPoints(), vertexCount * sizeof(FbxVector4));

			for(int i = 0; i < vertexCount; i++)
			{
				vertexArray[i] = (static_cast<FbxMatrix>(node->EvaluateGlobalTransform(FBXSDK_TIME_INFINITE)).MultNormalize(vertexArray[i]));
			}

			for(UInt32 i = 0; i < updateStructure.Count(); i++)
			{
				UpdateStructure us = updateStructure.Get(i);

				FbxVector4 position = vertexArray[us.VertexIndex];
				FbxVector2 uv = FbxVector2();
				if(us.UVIndex != -1)
					uv = mesh->GetElementUV(0)->GetDirectArray().GetAt(us.UVIndex);
				FbxVector4 normals = mesh->GetElementNormal(0)->GetDirectArray().GetAt(us.NormalIndex);
				FbxVector4 binormal = FbxVector4();
				FbxVector4 tangent = FbxVector4();


				SkinningVertex skin = {
					(float)position[0],(float)position[1],(float)position[2],
					(float)uv[0],(float)uv[1],
					(float)normals[0],(float)normals[1],(float)normals[2],
					us.Weights.X, us.Weights.Y, us.Weights.Z, us.Weights.W,
					us.Indices.X, us.Indices.Y, us.Indices.Z, us.Indices.W
				};
				verticesList.Set(i, skin);
			}
			delete[]vertexArray;
			vertexArray = 0;
		}

		bool TikiMesh::GetReady()
		{
			return this->updateStructure.Count() != 0;
		}

		int TikiMesh::MaxBonesPerVertex()
		{
			FbxMesh* mesh = this->node->GetMesh();
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
	}
}