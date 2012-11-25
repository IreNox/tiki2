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

		#pragma region Class
		TikiConvert(Model* model)
		{
			this->model = model;
			context = gcnew IOContext();

			meshIds = new List<UInt32>();
			animationIds = new List<UInt32>();

			addPartsModel();
		}

		TikiConvert(System::String^ fileName)
		{
			this->model = new Model();
			this->context = gcnew IOContext(fileName);

			meshIds = new List<UInt32>();
			animationIds = new List<UInt32>();

			readPartsModel();
		}

		~TikiConvert()
		{
			delete(meshIds);
			delete(animationIds);
		}
		#pragma endregion

		#pragma region Member
		Model* GetModel()
		{
			return model;
		}

		void WriteToFile(System::String^ fileName)
		{
			context->WriteToFile(fileName);
		}
		#pragma endregion
		
	private:

		Model* model;
		IOContext^ context;

		List<UInt32>* meshIds;
		List<UInt32>* animationIds;

		#pragma region Protected Member - Read
		void readPartsModel()
		{
			meshIds = new List<UInt32>((UInt32*)context->ReadPartPointer(context->GetHeader()->MeshArrayId), context->ReadPart(context->GetHeader()->MeshArrayId).ArrayCount, false);
			animationIds = new List<UInt32>((UInt32*)context->ReadPartPointer(context->GetHeader()->AnimationArrayId), context->ReadPart(context->GetHeader()->AnimationArrayId).ArrayCount, false);
			
			UInt32 i = 0;
			UInt32 id = 0;
			while (i < meshIds->Count())
			{
				id = animationIds->Get(i);

				model->GetMeshes()->Add(
					readTikiMesh(context->ReadPart(id), (BinaryTikiMesh*)context->ReadPartPointer(id))
				);
				i++;
			}

			i = 0;
			while (i < animationIds->Count())
			{
				id = animationIds->Get(i);

				model->GetAnimations()->Add(
					readTikiAnimation(context->ReadPart(id), (BinaryTikiAnimation*)context->ReadPartPointer(id))
				);
				i++;
			}

			id = context->GetHeader()->RootBoneId;
			model->SetRootBone(
				readTikiBone(context->ReadPart(id), (BinaryTikiBone*)context->ReadPartPointer(id), 0)
			);
		}

		TikiMesh* readTikiMesh(BinaryPart& part, BinaryTikiMesh* binMesh)
		{
			TikiMesh* mesh = new TikiMesh();

			//mesh->SetName(readString(binMesh->NameId));

			mesh->GetMaterial()->TexDiffuse = 0; //load from content manager
			mesh->GetMaterial()->TexNormalMap = 0; //load from content manager
			mesh->GetMaterial()->TexSpecular = 0; //load from content manager
			mesh->GetMaterial()->TexDiffuse = 0; //load from content manager

			//BinaryPart& dataPart = context->ReadPart(binMesh->VertexDataId);
			//
			//mesh->SetVertexData(
			//	context->ReadPartPointer(dataPart.Id),
			//	dataPart.Length * dataPart.ArrayCount
			//);

			//dataPart = context->ReadPart(binMesh->IndexDataId);

			//mesh->SetIndexData(
			//	context->ReadPartPointer(dataPart.Id),
			//	dataPart.Length * dataPart.ArrayCount
			//);

			//mesh->UseDeformation() = binMesh->UseDeformation;

			return mesh;
		}

		TikiAnimation* readTikiAnimation(BinaryPart& part, BinaryTikiAnimation* binAni)
		{
			TikiAnimation* ani = new TikiAnimation();

			ani->SetName(readString(binAni->NameId));
			ani->SetBSV(binAni->BSV);

			BinaryPart& ts = context->ReadPart(binAni->TimeStampsArrayId);
			double* time = (double*)context->ReadPartPointer(binAni->TimeStampsArrayId);

			UInt32 i = 0;
			while (i < ts.ArrayCount)
			{
				ani->AddTimeStampKey(time[i]);
				i++;
			}

			return ani;
		}

		TikiBone* readTikiBone(BinaryPart& part, BinaryTikiBone* binBone, TikiBone* parent)
		{
			TikiBone* bone = new TikiBone();

			bone->SetParent(parent);
			bone->SetName(readString(binBone->NameId));
			bone->SetBoneInitTransform(binBone->Init);
			bone->SetConstantBufferIndex(binBone->ConstanBufferIndex);

			BinaryPart& layerArr = context->ReadPart(binBone->LayerArrayId);
			UInt32* layerIds = (UInt32*)context->ReadPartPointer(binBone->LayerArrayId);

			UInt32 i = 0;
			while (i < layerArr.ArrayCount)
			{
				BinaryTikiLayer* binLayer = (BinaryTikiLayer*)context->ReadPartPointer(layerIds[i]);
				AnimationLayer layer;

				BinaryPart& arr = context->ReadPart(binLayer->RotationArrayId);

				layer.GetQuaternion() = List<Quaternion>(
					(Quaternion*)context->ReadPartPointer(arr.Id), arr.ArrayCount, false
				);

				arr = context->ReadPart(binLayer->TranslationArrayId);

				layer.GetTranslation() = List<Vector3>(
					(Vector3*)context->ReadPartPointer(arr.Id), arr.ArrayCount, false
				);

				bone->AddAnimation(
					model->GetAnimations()->Get(animationIds->IndexOf(binLayer->AnimationId)),
					layer
				);

				i++;
			}

			BinaryPart& childArr = context->ReadPart(binBone->ChildsArrayId);
			UInt32* childIds = (UInt32*)context->ReadPartPointer(binBone->ChildsArrayId);

			i = 0;
			while (i < childArr.ArrayCount)
			{
				bone->AddChild(
					readTikiBone(context->ReadPart(childIds[i]), (BinaryTikiBone*)context->ReadPartPointer(childIds[i]), bone)
				);
				i++;
			}

			return bone;
		}

		const char* readString(UInt32 id)
		{
			BinaryPart& part = context->ReadPart(id);

			char* str = new char[part.Length];
			memcpy(str, context->ReadPartPointer(id), part.Length);

			return str;
		}
		#pragma endregion

		#pragma region Protected Memer - Write
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
			btm->NameId = context->AddPart((void*)mesh->GetName(), 0, PT_String);
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
			while (i < animationIds->Count())
			{
				layer.Add(
					addPartsLayer(
						animationIds->Get(i),
						&bone->GetAnimationLayer(model->GetAnimations()->Get(i))
					)
				);
				i++;
			}
			btb->LayerArrayId = context->AddPart(layer.ToArray(), sizeof(UInt32), PT_Array, PT_UInt, layer.Count());

			return id;
		}

		UInt32 addPartsLayer(UInt32 animationId, AnimationLayer* layer)
		{
			BinaryTikiLayer* btl = new BinaryTikiLayer();

			btl->AnimationId = animationId;
			btl->RotationArrayId = context->AddPart((void*)layer->GetQuaternion().GetInternalData(), sizeof(Quaternion), PT_Array, PT_Quaternion, layer->GetQuaternion().Count());
			btl->TranslationArrayId = context->AddPart((void*)layer->GetTranslation().GetInternalData(), sizeof(Vector3), PT_Array, PT_Vector3, layer->GetTranslation().Count());

			return context->AddPart(btl, sizeof(BinaryTikiLayer), PT_Layer);
		}

		void addPartsAnimation(TikiAnimation* animation)
		{
			BinaryTikiAnimation* bta = new BinaryTikiAnimation();
			bta->NameId = context->AddPart((void*)animation->GetName(), 0, PT_String);

			bta->StartTime = animation->GetStartTime();
			bta->EndTime = animation->GetStopTime();

			bta->BSV = animation->GetBSV();

			bta->TimeStampsArrayId = context->AddPart((void*)animation->GetTimeStamps().GetInternalData(), sizeof(double), PT_Array, PT_Double, animation->GetTimeStamps().Count());

			animationIds->Add(
				context->AddPart(bta, sizeof(BinaryTikiAnimation), PT_Animation)
			);
		}
		#pragma endregion

	};
}