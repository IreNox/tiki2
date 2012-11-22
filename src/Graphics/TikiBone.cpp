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
			this->initInverse = init.Inverse();
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

			this->layer = new AnimationLayer();
			layer->AddRef();
			layer->Initialize(this->node, animation->Layer());

			for(int i = 0; i < childs.Count(); i++)
				childs[i]->InitializeAnimation(animation);
		}

		void TikiBone::Draw(const DrawArgs& args)
		{
			//if(parent != 0)
			//{
			//	Matrix s = Matrix::CreateScaleMatrix(0.01f,0.01f,0.01f);

			//	Vector3 p1 = Vector3::TransformCoordinate(Vector3(), BoneCurrentTransform() * s );
			//	Vector3 p2 = Vector3::TransformCoordinate(Vector3(), parent->BoneCurrentTransform() * s);

			//	FbxNodeAttribute::EType nodeType = node->GetNodeAttribute()->GetAttributeType();
			//	FbxNodeAttribute::EType parent;

			//	if(this->parent->node->GetNodeAttribute() == 0)
			//		parent = FbxNodeAttribute::eMesh;
			//	else
			//		parent = this->parent->node->GetNodeAttribute()->GetAttributeType();
			//	

			//	if(nodeType == FbxNodeAttribute::eSkeleton && parent == FbxNodeAttribute::eSkeleton)
			//	{
			//		args.Graphics->DrawLine(p1, p2, Color::Red);
			//	}
			//}

			for(int i = 0; i < childs.Count(); i++)
				childs[i]->Draw(args);
		}

		void TikiBone::Update(const UpdateArgs& args)
		{
			this->layer->Update(args.Time.ElapsedTime * 2.0f);

			if(this->parent == 0)
			{
				this->boneCurrent = layer->LocalTransform();
			}
			else
			{
				this->boneCurrent = layer->LocalTransform() * parent->BoneCurrentTransform();
			}

			for(UInt32 i = 0; i < childs.Count();i++)
			{
				childs[i]->Update(args);
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
			//return FBXConverter::Convert(this->shiftMatrix);
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
		TikiBone* TikiBone::GetBoneByIndex(int index)
		{
			if(this->constantBufferIndex == index)
				return this;
			for(int i = 0;  i< childs.Count(); i++)
			{
				TikiBone* tmp = childs[i]->GetBoneByIndex(index);
				if(tmp != 0)
					return tmp;
			}
		}

		const char* TikiBone::Name()
		{
			return name;
		}

		AnimationLayer* TikiBone::Layer()
		{
			return this->layer;
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

