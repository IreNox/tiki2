#include "Graphics/TikiBone.h"


namespace TikiEngine
{
	namespace Resources
	{

		TikiBone::TikiBone(FbxNode* node)
			:node(node), parent(0), childs(),
			boneInitTransform(), 
			boneInitTransformInverse(),
			boneCurrentTransform()
		{
		}

		TikiBone::~TikiBone()
		{

		}

		void TikiBone::Initialize()
		{
			name = node->GetName();

			for(int i = 0; i < node->GetChildCount(); i++)
			{
				TikiBone* tmp = new TikiBone(node->GetChild(i));
				tmp->SetParent(this);;
				tmp->Initialize();
				childs.Add(tmp);
			}

			if(this->parent != 0)
			{
				this->boneInitTransform =  parent->BoneInitTransform();
			}
			this->boneInitTransform = this->boneCurrentTransform = this->boneInitTransform * this->node->EvaluateLocalTransform();
			this->boneInitTransformInverse = this->boneInitTransform.Inverse();
		}

		void TikiBone::Update(FbxTime& time)
		{
			if(this->parent != 0)
			{
				this->boneCurrentTransform = parent->BoneCurrentTransform();
			}
			this->boneCurrentTransform *= this->node->EvaluateLocalTransform(time);
		}

		TikiBone* TikiBone::GetParent()
		{
			return this->parent;
		}
		void TikiBone::SetParent(TikiBone* parent)
		{
			this->parent = parent;
		}

		FbxAMatrix& TikiBone::BoneInitTransform()
		{
			return boneInitTransform;
		}

		FbxAMatrix& TikiBone::BoneCurrentTransform()
		{
			return boneCurrentTransform;
		}

		FbxAMatrix TikiBone::ShiftMatrix()
		{
			return this->boneInitTransformInverse * this->boneCurrentTransform;
		}

		int TikiBone::Count()
		{
			int count = 1;
			for(int i = 0; i < childs.Count(); i++)
			{
				count += childs[i]->Count();
			}
			return count;
		}
	}
}

