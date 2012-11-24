#pragma once

#include "Graphics/TikiMesh.h"
#include "Graphics/TikiBone.h"
#include "Graphics/FbxConverter.h"
#include "Graphics/TikiAnimation.h"

#define FBXSDK_NEW_API
#include "fbxsdk.h"

namespace TikiEngine
{
	namespace Resources
	{
		struct VertexBufferInput 
		{
			VertexBufferInput(){}
			VertexBufferInput(Vector3 position, Vector2 uv, Vector3 normal)
			{
				this->Position = position;
				this->UV = uv;
				this->Normal = normal;
			}

			inline bool operator==(const VertexBufferInput& rhs)
			{
				if(Position != rhs.Position || UV != rhs.UV || Normal != rhs.Normal)
					return false;
				return true;
			}

			Vector3 Position;
			Vector2 UV;
			Vector3 Normal;
		};
		struct SkinningInput
		{
			SkinningInput()
			{
				for(int i = 0; i < 4; i++)
				{
					Weights[i] = -1;
					Indices[i] = 0;
				}
			}
			float Weights[4];
			float Indices[4];
		};

		class FbxHelper
		{

		public:
			FbxHelper();
			~FbxHelper();

			void Initialize();

			FbxScene* GetScene();
			void SetScene(FbxScene* scene);

			TikiAnimation* GetAnimation();
			TikiBone* GetRootBone();
			List<TikiBone*>& GetConstantBufferIndices();
			List<TikiMesh*>& GetMeshes();

			static void MergeAnimation(TikiAnimation* animation, TikiBone* destination, TikiBone* source);

		private:

			void RecursiveBone(FbxNode* node);
			void BuildBoneHierachy(FbxNode* node, TikiBone* parent = 0);

			void InitializeAnimation();
			void InitializeAnimationLayer(FbxNode* node);
			void FillTimeStamp(FbxAnimCurve* curve);
			void FlagBones();
			void CleanBones();
			void FindMeshes();


			void InitializeMesh(FbxMesh* mesh);

			Matrix LocalTransform(FbxNode* node, FbxTime& time = FBXSDK_TIME_INFINITE);
			Matrix GlobalTransform(FbxNode* node, FbxTime& time = FBXSDK_TIME_INFINITE);
			int MaxBonesPerVertex(FbxMesh* mesh);

			void GetGlobalVertices(List<Vector3>& list, FbxMesh* mesh);

			FbxScene* scene;
			List<FbxNode*> fbxNodes;
			List<TikiBone*> tikiBones;
			TikiAnimation* animation;
			List<TikiMesh*> meshes;
			List<TikiBone*> constantBufferIndices;

			TikiBone* rootBone;

		};
	}
}