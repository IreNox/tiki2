#include "Graphics/TikiMesh.h"
#include "Graphics/Deformer.h"

namespace TikiEngine
{
	namespace Resources
	{
		TikiMesh::TikiMesh(Engine* engine, FbxNode* node)
			:engine(engine),
			node(node),
			indices(0),
			vertices(0),
			indicesCount(0),
			verticesSize(0),
			matrix(0)
		{

		}
		TikiMesh::~TikiMesh()
		{
		}
		void TikiMesh::Release()
		{
			node->Destroy();
		}
		bool TikiMesh::Initialize()
		{
			FbxMesh* mesh = node->GetMesh();

			int vertexCount = mesh->GetControlPointsCount();

			bool hasShape = mesh->GetShapeCount() > 0;
			bool hasSkin = mesh->GetDeformerCount(FbxDeformer::eSkin) > 0;
			this->hasDeformation = hasShape || hasSkin;

			FbxVector4* vertexArray = new FbxVector4[vertexCount];
			memcpy(vertexArray, mesh->GetControlPoints(), vertexCount * sizeof(FbxVector4));

			for(int i = 0; i < vertexCount; i++)
			{
				vertexArray[i] = (static_cast<FbxMatrix>(node->EvaluateGlobalTransform(FBXSDK_TIME_INFINITE)).MultNormalize(vertexArray[i]));
			}

			UInt32 counter = 0;

			for(Int32 i = 0; i < mesh->GetPolygonCount();i++)
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
					FbxVector4 binormal = FbxVector4();
					FbxVector4 tangent = FbxVector4();

					DefaultVertex default = {
						(float)position[0],(float)position[1],(float)position[2],
						(float)uv[0],(float)uv[1],
						(float)normals[0],(float)normals[1],(float)normals[2]
					};	

					indicesArray[k] = verticesList.IndexOf(default);
					if(indicesArray[k] == -1)
					{
						UpdateStructure us = {index, uvIndex, counter};
						this->updateStructure.Add(us);
						indicesArray[k] = verticesList.Count();
						verticesList.Add(default);
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

			return true;
		}

		void TikiMesh::Update(FbxTime& time, FbxAnimLayer* animLayer, FbxPose* pose)
		{
			if(!hasDeformation)
				return;

			FbxAMatrix globalPosition = node->EvaluateGlobalTransform(time);

			FbxMesh* mesh = node->GetMesh();

			int vertexCount = mesh->GetControlPointsCount();

			bool hasShape = mesh->GetShapeCount() > 0;

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

				DefaultVertex default = {
					(float)position[0],(float)position[1],(float)position[2],
					(float)uv[0],(float)uv[1],
					(float)normals[0],(float)normals[1],(float)normals[2]
				};	

				verticesList[i] = default;
			}
			delete[]vertexArray;
			vertexArray = 0;

		}

		bool TikiMesh::GetReady()
		{
			return this->updateStructure.Count() != 0;
		}
		#pragma endregion
	}
}