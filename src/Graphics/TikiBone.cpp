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
			for(UInt32 i = 0; i < childs.Count(); i++)
			{
				SafeRelease(&childs[i]);
			}
		}

		void TikiBone::Initialize()
		{
			name = node->GetName();

			if(this->parent != 0)
			{
				this->boneInitTransform =  parent->BoneInitTransform();
			}
			this->boneInitTransform = this->boneCurrentTransform = this->boneInitTransform * this->node->EvaluateLocalTransform();
			this->boneInitTransformInverse = this->boneInitTransform.Inverse();

			for(int i = 0; i < node->GetChildCount(); i++)
			{
				TikiBone* tmp = new TikiBone(node->GetChild(i));
				tmp->SetParent(this);;
				tmp->Initialize();
				childs.Add(tmp);
			}
		}

		void TikiBone::Update(FbxTime& time)
		{
			if(this->parent == 0)
			{
				this->boneCurrentTransform = node->EvaluateLocalTransform(time);
			}
			else
			{
				this->boneCurrentTransform = parent->BoneCurrentTransform() * node->EvaluateLocalTransform(time);
			}

			for(UInt32 i = 0; i < childs.Count();i++)
			{
				childs[i]->Update(time);
			}
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
			return this->boneCurrentTransform * this->boneInitTransformInverse;
		}

		int TikiBone::Count()
		{
			int count = 1;
			for(UInt32 i = 0; i < childs.Count(); i++)
			{
				count += childs[i]->Count();
			}
			return count;
		}

		TikiBone* TikiBone::GetBoneByName(const char* name)
		{
			if(this->name == name)
				return this;
			for(UInt32 i = 0; i < childs.Count();i++)
			{
				TikiBone* tmp = childs[i]->GetBoneByName(name);
				if(tmp != 0)
					return tmp;
			}
			return 0;
		}

		const char* TikiBone::Name()
		{
			return name;
		}
	}
}

