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



		private:

			void RecursiveBone(FbxNode* node);
			void BuildBoneHierachy(FbxNode* node, TikiBone* parent = 0);

			void InitializeAnimation();
			void InitializeAnimationLayer(FbxNode* node);
			void FillTimeStamp(FbxAnimCurve* curve);
			void FindMeshes();

			void InitializeMesh(FbxMesh* mesh);

			Matrix LocalTransform(FbxNode* node, FbxTime& time = FBXSDK_TIME_INFINITE);
			Matrix GlobalTransform(FbxNode* node, FbxTime& time = FBXSDK_TIME_INFINITE);

			FbxScene* scene;
			List<FbxNode*> fbxNodes;
			List<TikiBone*> tikiBones;
			TikiAnimation* animation;
			List<TikiMesh*> meshes;

			TikiBone* rootBone;

		};
	}
}