#pragma once

#include "Model.h"

#include "IOContext.h"

#include "BinaryTikiMesh.h"
#include "BinaryTikiBone.h"
#include "BinaryTikiLayer.h"
#include "BinaryTikiAnimation.h"

#include "Core/List.h"

namespace TikiEditor
{
	public ref class TikiConvert
	{
	public:

		TikiConvert(Model* model)
		{
			this->model = model;
			context = gcnew IOContext();

			meshIds = new List<UInt32>();
			animationIds = new List<UInt32>();

			addPartsModel();
		}

		~TikiConvert()
		{
			delete(meshIds);
			delete(animationIds);
		}

		void WriteToFile(System::String^ fileName)
		{
			context->WriteToFile(fileName);
		}

	private:

		Model* model;
		IOContext^ context;

		List<UInt32>* meshIds;
		List<UInt32>* animationIds;

		#pragma region Add Parts
		void addPartsModel()
		{
			UInt32 i = 0;
			while (i < model->GetMeshes()->Count())
			{
				addPartsMesh(
					model->GetMeshes()->Get(i)
				);
				i++;
			}

			i = 0;
			while (i < model->GetAnimations()->Count())
			{
				addPartsAnimation(
					model->GetAnimations()->Get(i)
				);
				i++;
			}

			context->GetHeader()->RootBoneId = addPartsBone(model->GetRootBone(), 0);
			context->GetHeader()->MeshArrayId = context->AddPart((void*)meshIds->GetInternalData(), sizeof(UInt32), PT_Array, PT_UInt, meshIds->Count());
			context->GetHeader()->AnimationArrayId = context->AddPart((void*)animationIds->GetInternalData(), sizeof(UInt32), PT_Array, PT_UInt, animationIds->Count());
		}

		void addPartsMesh(TikiMesh* mesh)
		{
			BinaryTikiMesh* btm = new BinaryTikiMesh();
			btm->NameId = context->AddPart(mesh->GetName(), PT_String, PT_NoArray);
			btm->VertexDataId = context->AddPart((void*)mesh->verticesList.GetInternalData(), sizeof(SkinningVertex), PT_Array, PT_Byte, mesh->verticesList.Count());
			btm->IndexDataId = context->AddPart((void*)mesh->indicesList.GetInternalData(), sizeof(UInt32), PT_Array, PT_UInt, mesh->indicesList.Count());

			btm->UseDeformation = mesh->UseDeformation();

			btm->DiffuseTexId = addPartsTexture(mesh->GetMaterial()->TexDiffuse);
			btm->NormalTexId  = addPartsTexture(mesh->GetMaterial()->TexNormalMap);
			btm->SpecTexId    = addPartsTexture(mesh->GetMaterial()->TexSpecular);
			btm->LightTexId   = addPartsTexture(mesh->GetMaterial()->TexDiffuse);

			meshIds->Add(
				context->AddPart(btm, PT_Mesh, PT_NoArray)
			);
		}

		UInt32 addPartsTexture(ITexture* tex)
		{
			if (tex != 0)
			{
				string name = StringWtoA(tex->GetFileName());

				return context->AddPart((void*)name.c_str(), 0, PT_String);
			}

			return 0;
		}

		UInt32 addPartsBone(TikiBone* bone, UInt32 parentId)
		{
			BinaryTikiBone* btb = new BinaryTikiBone();
			btb->NameId = context->AddPart((void*)bone->GetName(), 0, PT_String);
			btb->ParentId = parentId;
			btb->Init = bone->BoneInitTransform();
			btb->ConstanBufferIndex = bone->GetConstantBufferIndex();			

			UInt32 id = context->AddPart(btb, sizeof(BinaryTikiBone), PT_Bone);

			UInt32 i = 0;
			List<UInt32> childs;
			while (i < bone->GetChilds()->Count())
			{
				childs.Add(
					addPartsBone(bone->GetChilds()->Get(i), id)
				);
				i++;
			}
			btb->ChildsArrayId = context->AddPart(childs.ToArray(), sizeof(UInt32), PT_Array, PT_UInt, childs.Count());

			i = 0;
			List<UInt32> layer;
			while (i < bone->GetAnimationLayer()->Count())
			{
				layer.Add(
					addPartsLayer(bone->GetAnimationLayer()->Get(i), id)
				);
				i++;
			}
			btb->LayerArrayId = context->AddPart(layer.ToArray(), sizeof(UInt32), PT_Array, PT_UInt, layer.Count());

			return id;
		}

		UInt32 addPartsLayer(AnimationLayer* layer)
		{
			BinaryTikiLayer* btl = new BinaryTikiLayer();
			btl->NameId = context->AddPart(layer->GetName(), 0, PT_String);

			btl->RotationArrayId = context->AddPart(layer->GetQuaternion().GetInternalData(), sizeof(Quaternion), PT_Array, PT_Quaternion, layer->GetQuaternion().Count());
			btl->TranslationArrayId = context->AddPart(layer->GetTranslation()->GetInternalData(), sizeof(Vector3), PT_Array, PT_Vector3, layer->GetTranslation().Count());

			return context->AddPart(btl, sizeof(BinaryTikiLayer), PT_Layer);
		}

		void addPartsAnimation(TikiAnimation* animation)
		{
			BinaryTikiAnimation* bta = new BinaryTikiAnimation();
			bta->NameId = context->AddPart(animation->GetName(), PT_String, PT_NoArray);

			bta->StartTime = animation->GetStart();
			bta->EndTime = animation->GetEnd();

			bta->BSV = animation->GetBSV();

			bta->TimeStampsArrayId = context->AddPart(animation->GetTmeStamps()->GetInternalData(), PT_Array, PT_Double, animation->GetTimeStamps()->Count());

			animationIds.Add(
				context->AddPart(bta, PT_Animation)
			);
		}
		#pragma endregion

	};
}