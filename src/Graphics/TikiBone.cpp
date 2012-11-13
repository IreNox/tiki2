#include "Graphics/TikiBone.h"


namespace TikiEngine
{
	namespace Resources
	{

		TikiBone::TikiBone(FbxNode* node)
			:node(node), parent(0), childs(),
			boneInit(), 
			boneInitInverse(),
			boneCurrent(),
			constantBufferIndex(-1),
			layer(0)
		{
		}

		TikiBone::~TikiBone()
		{
			//SafeRelease(&parent);
			SafeRelease(&layer);

			for(UInt32 i = 0; i < childs.Count(); i++)
			{
				SafeRelease(&childs[i]);
			}
		}
		void TikiBone::SetBind(FbxAMatrix& init)
		{
			this->boneInit = FBXConverter::ConvertTranspose(init);
			this->boneInitInverse = FBXConverter::ConvertTranspose(init.Inverse());
		}

		void TikiBone::Initialize()
		{
			name = node->GetName();

			if(this->parent != 0)
			{
				this->boneInit =  parent->BoneInitTransform();
			}
			this->boneInit = this->boneCurrent = FBXConverter::ConvertTranspose(node->EvaluateLocalTransform()) * this->boneInit;
			this->boneInitInverse = FBXConverter::ConvertTranspose(node->EvaluateLocalTransform().Inverse());

			for(int i = 0; i < node->GetChildCount(); i++)
			{
				TikiBone* tmp = new TikiBone(node->GetChild(i));
				tmp->AddRef();
				tmp->SetParent(this);;
				tmp->Initialize();
				childs.Add(tmp);
			}
		}

		void TikiBone::Clean()
		{
			for(int i = 0; i < childs.Count(); i++)
			{
				childs[i]->Clean();

				if(childs[i]->childs.Count() == 0 && childs[i]->constantBufferIndex == -1)
				{
					childs[i]->Release();
					childs.RemoveAt(i);
				}
			}
		}

		void TikiBone::CreateMapping(List<TikiBone*>& list)
		{
			if(constantBufferIndex != -1)
				list.Add(this);
			constantBufferIndex = list.Count() - 1;
			for(int i = 0; i < childs.Count(); i++)
				childs[i]->CreateMapping(list);
		}

		void TikiBone::InitializeAnimation(TikiAnimation* animation)
		{
			if(this->layer != 0)
				return;

			this->layer = new AnimationLayer(animation->StartTime(), animation->StopTime());
			layer->AddRef();
			layer->Initialize(this->node, animation->Layer());

			for(int i = 0; i < childs.Count(); i++)
				childs[i]->InitializeAnimation(animation);
		}

		void TikiBone::Update(const double& time)
		{
			if(this->parent == 0)
			{
				//this->boneCurrentTransform = node->EvaluateLocalTransform(fbxTime);
				this->boneCurrent = layer->LocalTransform(time);
			}
			else
			{
				//this->boneCurrentTransform = parent->BoneCurrentTransform() * node->EvaluateLocalTransform(fbxTime);
				this->boneCurrent = layer->LocalTransform(time) * parent->BoneCurrentTransform();
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
			//SafeAddRef(parent, &this->parent);
		}

		Matrix& TikiBone::BoneInitTransform()
		{
			return boneInit;
		}

		Matrix& TikiBone::BoneCurrentTransform()
		{
			return boneCurrent;
		}

		Matrix TikiBone::ShiftMatrix()
		{
			return (this->boneInitInverse * this->boneCurrent).Transpose();
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

		int TikiBone::GetConstantBufferIndex()
		{
			return this->constantBufferIndex;
		}

		void TikiBone::SetConstantBufferIndex(int index)
		{
			this->constantBufferIndex = index;
		}
	}
}

