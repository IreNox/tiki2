#pragma once

#include "Graphics/TikiBone.h"
#include "Graphics/FbxConverter.h"

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

			TikiBone* GetRootBone();



		private:

			void RecursiveBone(FbxNode* node);
			void BuildBoneHierachy(FbxNode* node, TikiBone* parent = 0);

			Matrix LocalTransform(FbxNode* node, FbxTime& time = FBXSDK_TIME_INFINITE);
			Matrix GlobalTransform(FbxNode* node, FbxTime& time = FBXSDK_TIME_INFINITE);

			FbxScene* scene;
			List<FbxNode*> fbxNodes;
			List<TikiBone*> tikiBones;

			TikiBone* rootBone;

		};
	}
}