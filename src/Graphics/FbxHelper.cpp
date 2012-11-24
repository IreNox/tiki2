#include "Graphics/FbxHelper.h"

namespace TikiEngine
{
	namespace Resources
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

		void FbxHelper::Initialize()
		{
			FbxNode* root = this->scene->GetRootNode();
			RecursiveBone(root);
			BuildBoneHierachy(root);

			InitializeAnimation();

			for(int i = 0; i < fbxNodes.Count(); i++)
				InitializeAnimationLayer(fbxNodes[i]);

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

		void FbxHelper::FindMeshes()
		{
			int meshCount = scene->GetSrcObjectCount<FbxMesh>();
			for(int i = 0; i < meshCount; i++)
			{
				FbxMesh* mesh = scene->GetSrcObject<FbxMesh>(i);

				this->InitializeMesh(mesh);
			}
		}

		void FbxHelper::InitializeMesh(FbxMesh* mesh)
		{

		}

		void FbxHelper::InitializeAnimation()
		{
			this->animation = new TikiAnimation();

			FbxAnimStack* stack = scene->GetSrcObject<FbxAnimStack>(0);
			animation->SetName(stack->GetName());

			for(int layerIndex = 0; layerIndex < stack->GetSrcObjectCount(); layerIndex++)
			{
				FbxAnimLayer* layer = stack->GetSrcObject<FbxAnimLayer>(layerIndex);
				for(int i = 0; i < fbxNodes.Count(); i++)
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

			int bsv = 1;
			while(bsv*2 < animation->GetTimeStamps().Count())
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
			TikiBone* bone;
			for(int i = 0; i < tikiBones.Count(); i++)
			{
				if(node->GetName() == tikiBones[i]->GetName())
				{
					bone = tikiBones[i];
					break;
				}
			}
			AnimationLayer layer;

			if(animation->GetTimeStamps().Count() == 0) // defaultValues
			{
				FbxAMatrix transform = node->EvaluateLocalTransform();

				layer.GetTranslation().Add(FBXConverter::ConvertDrop(transform.GetT()));
				layer.GetQuaternion().Add(FBXConverter::Convert(transform.GetQ()));
			}
			else
			{
				for(int i = 0; i < animation->GetTimeStamps().Count(); i++)
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