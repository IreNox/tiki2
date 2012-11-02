#pragma once

#include "Core/TypeGlobals.h"

#include "Core/List.h"
#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"
#include "Core/IModel.h"
#include "Graphics/TikiBone.h"

#define FBXSDK_NEW_API
#include "fbxsdk.h"

using namespace TikiEngine::Vertices;

namespace TikiEngine
{
	namespace Resources
	{
		struct UpdateStructure
		{
			int VertexIndex;
			int UVIndex;
			int NormalIndex;
			Vector4 Weights;
			Vector4 Indices;
		};

		class TikiMesh : public TikiObject
		{

		public:

			TikiMesh(Engine* engine, FbxNode* node);
			~TikiMesh();

			bool Initialize();
			void InitializeGPUSkinning();
			void InitializeBones(TikiBone& rootBone);

			void Update(FbxTime& time, FbxAnimLayer* animLayer, FbxPose* pose);
			void UpdateVertexBuffer();

			bool GetReady();

			List<SkinningVertex> verticesList;
			List<UInt32> indicesList;
			List<Matrix> skinMatrices;

			List<TikiBone*> bones;

			
		private:

			void ComputeClusterDeformation(FbxAMatrix& pGlobalPosition, FbxMesh* pMesh, FbxCluster* pCluster, 
				FbxAMatrix& pVertexTransformMatrix, FbxTime pTime, FbxPose* pPose);
			FbxAMatrix GetGeometry(FbxNode* pNode);

			int MaxBonesPerVertex();

			FbxNode* node;
			Engine* engine;

			List<UpdateStructure> updateStructure;

			bool hasDeformation;
		};
	}
}
