#include "Graphics/FbxHelper.h"

namespace TikiEngine
{
	namespace Resources
	{
		FbxHelper::FbxHelper()
			: scene(0), rootBone(0)
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

		void FbxHelper::Initialize()
		{
			FbxNode* root = this->scene->GetRootNode();
			RecursiveBone(root);
			BuildBoneHierachy(root);

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
			bone->SetFbxNode(node); //TODO kicken

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



#pragma region NodeHelper
		Matrix FbxHelper::LocalTransform(FbxNode* node, FbxTime& time )
		{
			return FBXConverter::ConvertTranspose(node->EvaluateLocalTransform(time));
		}

		Matrix FbxHelper::GlobalTransform(FbxNode* node, FbxTime& time )
		{
			return FBXConverter::ConvertTranspose(node->EvaluateGlobalTransform(time));
		}
#pragma endregion

	}
}