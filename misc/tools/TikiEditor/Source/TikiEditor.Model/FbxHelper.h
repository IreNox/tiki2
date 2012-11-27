#pragma once

#include "Graphics/TikiMesh.h"
#include "Graphics/TikiBone.h"
#include "Graphics/TikiAnimation.h"

#include "FBXConverter.h"

#define FBXSDK_NEW_API
#include "fbxsdk.h"

namespace TikiEditor
{
	using namespace TikiEngine::Resources;

	class FbxHelper
	{

	public:
		FbxHelper();
		~FbxHelper();

		void Initialize();

		FbxScene* GetScene();
		void SetScene(FbxScene* scene);

		List<const char *> GetMeshNames(FbxScene* scene);

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
		void CleanBones(TikiBone* bone);
		void FindMeshes();


		void InitializeMesh(FbxMesh* mesh);

		Matrix LocalTransform(FbxNode* node, FbxTime& time = FBXSDK_TIME_INFINITE);
		Matrix GlobalTransform(FbxNode* node, FbxTime& time = FBXSDK_TIME_INFINITE);
		int MaxBonesPerVertex(FbxMesh* mesh);

		void GetGlobalVertices(List<Vector3>& list, FbxMesh* mesh);
		void InitializeBufferData(List<Vector3>& vertices, List<SkinningVertex>& buffer, List<UInt32>& indices, FbxMesh* mesh);
		void GetSkinningCluster(FbxMesh* mesh, List<FbxCluster*>& clusterList);
		void InitializeSkinning(FbxMesh* mesh, List<Vector3>& vertices, List<SkinningVertex>& buffer);

		FbxScene* scene;
		List<FbxNode*> fbxNodes;
		List<TikiBone*> tikiBones;
		TikiAnimation* animation;
		List<TikiMesh*> meshes;
		List<TikiBone*> constantBufferIndices;

		TikiBone* rootBone;

	};
}