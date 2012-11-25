
#include "Graphics/ModelConverter.h"

#ifdef TIKI_ENGINE
#include "Core/IContentManager.h"
#endif

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		ModelConverter::ModelConverter(Model* model)
			: meshIds(), animationIds(), constantBufferIndices()
		{
			SafeAddRef(model, &this->model);
			context = new ModelIOContext();

			addPartsModel();
		}

		ModelConverter::ModelConverter(Model* model, Stream* stream)
			: meshIds(), animationIds(), constantBufferIndices()
		{
			SafeAddRef(model, &this->model);
			this->context = new ModelIOContext(stream);

			readPartsModel();
		}

		ModelConverter::~ModelConverter()
		{
			SafeDelete(&context);
			SafeRelease(&model);
		}
		#pragma endregion

		#pragma region Member
		Model* ModelConverter::GetModel()
		{
			return model;
		}

		void ModelConverter::WriteToStream(Stream* stream)
		{
			context->WriteToStream(stream);
		}
		#pragma endregion

		#pragma region Protected Member - Read
		void ModelConverter::readPartsModel()
		{
			meshIds = List<UInt32>((UInt32*)context->ReadPartPointer(context->GetHeader()->MeshArrayId), context->ReadPart(context->GetHeader()->MeshArrayId).ArrayCount, false);
			animationIds = List<UInt32>((UInt32*)context->ReadPartPointer(context->GetHeader()->AnimationArrayId), context->ReadPart(context->GetHeader()->AnimationArrayId).ArrayCount, false);

			UInt32 i = 0;
			UInt32 id = 0;
			while (i < meshIds.Count())
			{
				id = animationIds[i];

				model->GetMeshes()->Add(
					readTikiMesh(context->ReadPart(id), (BinaryTikiMesh*)context->ReadPartPointer(id))
				);
				i++;
			}

			i = 0;
			while (i < animationIds.Count())
			{
				id = animationIds[i];

				model->GetAnimations()->Add(
					readTikiAnimation(context->ReadPart(id), (BinaryTikiAnimation*)context->ReadPartPointer(id))
				);
				i++;
			}

			id = context->GetHeader()->RootBoneId;
			model->SetRootBone(
				readTikiBone(context->ReadPart(id), (BinaryTikiBone*)context->ReadPartPointer(id), 0)
			);

			model->SetConstantBufferIndices(
				constantBufferIndices
			);
		}

		TikiMesh* ModelConverter::readTikiMesh(BinaryPart& part, BinaryTikiMesh* binMesh)
		{
			TikiMesh* mesh = new TikiMesh();

			mesh->SetName(readString(binMesh->NameId));
			mesh->SetDeformation(binMesh->UseDeformation);

#ifdef TIKI_ENGINE
			if (binMesh->UseDeformation)
			{
				mesh->SetMaterial(model->GetEngine()->content->LoadMaterial(L"os_skinning"));
			}
			else
			{
				mesh->SetMaterial(model->GetEngine()->content->LoadMaterial(L"os_default"));
			}

			mesh->GetMaterial()->TexDiffuse = 0; //load from content manager
			mesh->GetMaterial()->TexNormalMap = 0; //load from content manager
			mesh->GetMaterial()->TexSpecular = 0; //load from content manager
			mesh->GetMaterial()->TexDiffuse = 0; //load from content manager
#endif

			BinaryPart& dataPart = context->ReadPart(binMesh->VertexDataId);
			
			List<SkinningVertex> vertices = List<SkinningVertex>(
				(SkinningVertex*)context->ReadPartPointer(dataPart.Id),
				dataPart.ArrayCount,
				false
			);
			mesh->SetSkinningVertexData(vertices);


			dataPart = context->ReadPart(binMesh->IndexDataId);

			List<UInt32> indices = List<UInt32>(
				(UInt32*)context->ReadPartPointer(dataPart.Id),
				dataPart.ArrayCount,
				false
			);
			mesh->SetIndices(indices);

			return mesh;
		}

		TikiAnimation* ModelConverter::readTikiAnimation(BinaryPart& part, BinaryTikiAnimation* binAni)
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

		TikiBone* ModelConverter::readTikiBone(BinaryPart& part, BinaryTikiBone* binBone, TikiBone* parent)
		{
			TikiBone* bone = new TikiBone();

			bone->SetParent(parent);
			bone->SetName(readString(binBone->NameId));
			bone->SetBoneInitTransform(binBone->Init);
			bone->SetConstantBufferIndex(binBone->ConstanBufferIndex);

			while (constantBufferIndices.Count() < binBone->ConstanBufferIndex)	{ }
			constantBufferIndices[binBone->ConstanBufferIndex] = bone;

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
					model->GetAnimations()->Get(animationIds.IndexOf(binLayer->AnimationId)),
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

		const char* ModelConverter::readString(UInt32 id)
		{
			BinaryPart& part = context->ReadPart(id);

			char* str = new char[part.Length];
			memcpy(str, context->ReadPartPointer(id), part.Length);

			return str;
		}
		#pragma endregion

		#pragma region Protected Memer - Write
		void ModelConverter::addPartsModel()
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
			context->GetHeader()->MeshArrayId = context->AddPart((void*)meshIds.GetInternalData(), sizeof(UInt32), PT_Array, PT_UInt, meshIds.Count());
			context->GetHeader()->AnimationArrayId = context->AddPart((void*)animationIds.GetInternalData(), sizeof(UInt32), PT_Array, PT_UInt, animationIds.Count());
		}

		void ModelConverter::addPartsMesh(TikiMesh* mesh)
		{
			BinaryTikiMesh* btm = new BinaryTikiMesh();
			btm->NameId = context->AddPart((void*)mesh->GetName(), 0, PT_String);
			btm->VertexDataId = context->AddPart((void*)mesh->verticesList.GetInternalData(), sizeof(SkinningVertex), PT_Array, PT_Byte, mesh->verticesList.Count());
			btm->IndexDataId = context->AddPart((void*)mesh->indicesList.GetInternalData(), sizeof(UInt32), PT_Array, PT_UInt, mesh->indicesList.Count());

			btm->UseDeformation = mesh->UseDeformation();

			Material* mat = mesh->GetMaterial();

			if (mat != 0)
			{
				btm->DiffuseTexId = addPartsTexture(mat->TexDiffuse);
				btm->NormalTexId  = addPartsTexture(mat->TexNormalMap);
				btm->SpecTexId    = addPartsTexture(mat->TexSpecular);
				btm->LightTexId   = addPartsTexture(mat->TexDiffuse);
			}

			meshIds.Add(
				context->AddPart(btm, sizeof(BinaryTikiMesh), PT_Mesh)
			);
		}

		UInt32 ModelConverter::addPartsTexture(ITexture* tex)
		{
			if (tex != 0)
			{
				string name = StringWtoA(tex->GetFileName());

				return context->AddPart((void*)name.c_str(), 0, PT_String);
			}

			return 0;
		}

		UInt32 ModelConverter::addPartsBone(TikiBone* bone, UInt32 parentId)
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
			while (i < animationIds.Count())
			{
				layer.Add(
					addPartsLayer(
					animationIds[i],
					&bone->GetAnimationLayer(model->GetAnimations()->Get(i))
					)
					);
				i++;
			}
			btb->LayerArrayId = context->AddPart(layer.ToArray(), sizeof(UInt32), PT_Array, PT_UInt, layer.Count());

			return id;
		}

		UInt32 ModelConverter::addPartsLayer(UInt32 animationId, AnimationLayer* layer)
		{
			BinaryTikiLayer* btl = new BinaryTikiLayer();

			btl->AnimationId = animationId;
			btl->RotationArrayId = context->AddPart((void*)layer->GetQuaternion().GetInternalData(), sizeof(Quaternion), PT_Array, PT_Quaternion, layer->GetQuaternion().Count());
			btl->TranslationArrayId = context->AddPart((void*)layer->GetTranslation().GetInternalData(), sizeof(Vector3), PT_Array, PT_Vector3, layer->GetTranslation().Count());

			return context->AddPart(btl, sizeof(BinaryTikiLayer), PT_Layer);
		}

		void ModelConverter::addPartsAnimation(TikiAnimation* animation)
		{
			BinaryTikiAnimation* bta = new BinaryTikiAnimation();
			bta->NameId = context->AddPart((void*)animation->GetName(), 0, PT_String);

			bta->StartTime = animation->GetStartTime();
			bta->EndTime = animation->GetStopTime();

			bta->BSV = animation->GetBSV();

			bta->TimeStampsArrayId = context->AddPart((void*)animation->GetTimeStamps().GetInternalData(), sizeof(double), PT_Array, PT_Double, animation->GetTimeStamps().Count());

			animationIds.Add(
				context->AddPart(bta, sizeof(BinaryTikiAnimation), PT_Animation)
			);
		}
		#pragma endregion

	}
}