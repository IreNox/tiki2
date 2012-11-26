
#include "Graphics/ModelConverter.h"

#ifdef TIKI_ENGINE
#include "Core/IContentManager.h"
#endif

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region ModelIOContext
		#pragma region Class
		ModelIOContext::ModelIOContext()
			: binaryPartPointer(), binaryParts(), data(0)
		{
		}

		ModelIOContext::ModelIOContext(Stream* stream)
			: binaryParts(), binaryPartPointer()
		{
			UInt32 len = (UInt32)stream->GetLength();

			data = new Byte[len];
			stream->Read(data, 0, len);

			readHeader();
			readParts();
		}

		ModelIOContext::~ModelIOContext()
		{
			SafeDeleteArray(&data);
		}
		#pragma endregion

		#pragma region Member
		BinaryFileHeader* ModelIOContext::GetHeader()
		{
			return &binaryHeader;
		}
		#pragma endregion

		#pragma region Member - Read
		void* ModelIOContext::ReadPartPointer(UInt32 id)
		{
			return binaryPartPointer[id];
		}

		BinaryPart& ModelIOContext::ReadPart(UInt32 id)
		{
			return binaryParts[id];
		}
		#pragma endregion

		#pragma region Member - Write
		UInt32 ModelIOContext::AddPart(void* pointer, UInt32 length, PartType type)
		{
			return this->AddPart(pointer, length, type, PT_NoArray, 1);
		}

		UInt32 ModelIOContext::AddPart(void* pointer, UInt32 length, PartType type, PartType arrayOf, UInt32 arrayCount)
		{
			if (type == PT_String)
			{
				length = (UInt32)strlen((char*)pointer) + 1;
			}

			BinaryPart bp;
			bp.Id = binaryParts.Count();
			bp.Length = length;

			bp.Type = type;
			bp.ArrayOf = arrayOf;
			bp.ArrayCount = arrayCount;

			binaryPartPointer.Add(pointer);
			binaryParts.Add(bp);

			return bp.Id;
		}

		void ModelIOContext::WriteToStream(Stream* stream)
		{
			writeInitData();
			writeToData();

			stream->Write(data, 0, binaryHeader.FileLength);
		}
		#pragma endregion

		#pragma region Protected Member - Read
		void ModelIOContext::readHeader()
		{
			memcpy(&binaryHeader, data, sizeof(BinaryFileHeader));
		}

		void ModelIOContext::readParts()
		{
			BinaryPart* parts = new BinaryPart[binaryHeader.PartCount];
			memcpy(parts, data + sizeof(BinaryFileHeader), sizeof(BinaryPart) * binaryHeader.PartCount);

			UInt32 i = 0;
			while (i < binaryHeader.PartCount)
			{
				binaryPartPointer.Add(data + parts[i].Start);
				i++;
			}

			binaryParts = List<BinaryPart>(parts, binaryHeader.PartCount, false);
			delete[](parts);
		}
		#pragma endregion

		#pragma region Protected Member - Write
		void ModelIOContext::writeInitData()
		{
			binaryHeader.TIKI[0] = 'T';
			binaryHeader.TIKI[1] = 'I';
			binaryHeader.TIKI[2] = 'K';
			binaryHeader.TIKI[3] = 'I';
			binaryHeader.PartCount = binaryParts.Count();

			UInt32 pos = sizeof(BinaryFileHeader);
			pos += sizeof(BinaryPart) * binaryHeader.PartCount;

			UInt32 i = 0;
			while (i < binaryParts.Count())
			{
				BinaryPart& bp = binaryParts.GetRef(i);				
				bp.Start = pos;

				pos += bp.Length * bp.ArrayCount;
				i++;
			}

			binaryHeader.FileLength = pos;
		}

		void ModelIOContext::writeToData()
		{
			data = new Byte[binaryHeader.FileLength];
			Byte* writeTo = data;

			UInt32 i = sizeof(BinaryFileHeader);
			memcpy(writeTo, &binaryHeader, i);
			writeTo += i;

			i = sizeof(BinaryPart) * binaryHeader.PartCount;
			memcpy(writeTo, binaryParts.GetInternalData(), i);
			writeTo += i;

			i = 0;
			while (i < binaryParts.Count())
			{				
				BinaryPart& bp = binaryParts.GetRef(i);
				UInt32 len = bp.Length * bp.ArrayCount;

				if (len > 0)
				{
					memcpy(writeTo, binaryPartPointer.Get(i), len);
				}

				writeTo += len;
				i++;
			}		
		}
		#pragma endregion
		#pragma endregion

		#pragma region ModelConverter
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
				id = meshIds[i];

				model->GetMeshes()->Add(
					readTikiMesh(context->ReadPart(id), (BinaryTikiMesh*)context->ReadPartPointer(id))
				);
				i++;
			}

			i = 0;
			while (i < animationIds.Count())
			{
				id = animationIds[i];

				model->AddAnimation(
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
			mesh->SetDeformation(binMesh->UseDeformation != 0);

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

			if (binBone->ConstanBufferIndex >= 0)
			{
				while (constantBufferIndices.Count() <= (UInt32)binBone->ConstanBufferIndex) { constantBufferIndices.Add(0); }
				constantBufferIndices[binBone->ConstanBufferIndex] = bone;
			}

			BinaryPart& layerArr = context->ReadPart(binBone->LayerArrayId);
			UInt32* layerIds = (UInt32*)context->ReadPartPointer(binBone->LayerArrayId);

			UInt32 i = 0;
			while (i < layerArr.ArrayCount)
			{
				BinaryTikiLayer* binLayer = (BinaryTikiLayer*)context->ReadPartPointer(layerIds[i]);
				TikiLayer layer;

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

		string ModelConverter::readString(UInt32 id)
		{
			BinaryPart& part = context->ReadPart(id);

			char* cstr = new char[part.Length];
			memcpy(cstr, context->ReadPartPointer(id), part.Length);

			string str = cstr;
			delete[](cstr);

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
			btm->NameId = context->AddPart((void*)mesh->GetName().c_str(), 0, PT_String);
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
			btb->NameId = context->AddPart((void*)bone->GetName().c_str(), 0, PT_String);
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

		UInt32 ModelConverter::addPartsLayer(UInt32 animationId, TikiLayer* layer)
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
			bta->NameId = context->AddPart((void*)animation->GetName().c_str(), 0, PT_String);

			bta->StartTime = animation->GetStartTime();
			bta->EndTime = animation->GetStopTime();

			bta->BSV = animation->GetBSV();

			bta->TimeStampsArrayId = context->AddPart((void*)animation->GetTimeStamps().GetInternalData(), sizeof(double), PT_Array, PT_Double, animation->GetTimeStamps().Count());

			animationIds.Add(
				context->AddPart(bta, sizeof(BinaryTikiAnimation), PT_Animation)
			);
		}
		#pragma endregion
		#pragma endregion

		#pragma region TikiMesh
		TikiMesh::TikiMesh()
			: material(0), hasDeformation(false)
		{
		}

		TikiMesh::~TikiMesh()
		{
			SafeRelease(&material);
		}

		string TikiMesh::GetName()
		{
			return this->name;
		}

		void TikiMesh::SetName(string name)
		{
			this->name = name;
		}

		void TikiMesh::SetDeformation(bool b)
		{
			hasDeformation = b;
		}

		bool TikiMesh::UseDeformation()
		{
			return hasDeformation;
		}

		Material* TikiMesh::GetMaterial()
		{
			return material;
		}

		void TikiMesh::SetMaterial(Material* material)
		{
			SafeRelease(&this->material);
			SafeAddRef(material, &this->material);
		}

		bool TikiMesh::GetReady()
		{
			return this->verticesList.Count() != 0 && this->indicesList.Count() != 0;
		}

		void TikiMesh::SetIndices(List<UInt32>& indices)
		{
			this->indicesList = indices;
		}

		void TikiMesh::SetSkinningVertexData(List<SkinningVertex>& skinning)
		{
			this->verticesList = skinning;
		}
		#pragma endregion

		#pragma region TikiBone
		TikiBone::TikiBone()
			:parent(0), childs(), boneInit(), boneInitInverse(), boneCurrent(), constantBufferIndex(-1)
		{
		}

		TikiBone::~TikiBone()
		{
			for(UInt32 i = 0; i < childs.Count(); i++)
			{
				SafeRelease(&childs[i]);
			}
		}

		void TikiBone::AddChild(TikiBone* bone)
		{
			bone->AddRef();
			this->childs.Add(bone);
		}

		List<TikiBone*>* TikiBone::GetChilds()
		{
			return &childs;
		}

		void TikiBone::Clean()
		{
			for(UINT i = 0; i < childs.Count(); i++)
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
			for(UInt32 i = 0; i < childs.Count(); i++)
				childs[i]->CreateMapping(list);
		}

		void TikiBone::Draw(const DrawArgs& args)
		{
			for(UInt32 i = 0; i < childs.Count(); i++)
				childs[i]->Draw(args);
		}

		void TikiBone::Update(List<TikiAnimation*>& animations)
		{
			Matrix shift;

			for(UInt32 i = 0; i < animations.Count(); i++)
			{
				TikiAnimation* anim = animations[i];
				TikiLayer& layer = animationData.GetRef(anim);

				layer.Update(anim);
				shift = layer.LocalTransform();
			}

			if(this->parent == 0)
			{
				this->boneCurrent = shift;
			}
			else
			{
				this->boneCurrent = shift * parent->BoneCurrentTransform();
			}

			for(UInt32 i = 0; i < childs.Count();i++)
			{
				childs[i]->Update(animations);
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

		Matrix& TikiBone::BoneInitTransform()
		{
			return boneInit;
		}

		Matrix& TikiBone::BoneCurrentTransform()
		{
			return boneCurrent;
		}

		void TikiBone::SetBoneInitTransform(Matrix& mat)
		{
			this->boneInit = mat;
			this->boneInitInverse = mat.Invert();
		}

		void TikiBone::SetBoneCurrentTransform(Matrix& mat)
		{
			this->boneCurrent = mat;
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
			if(this->name == string(name))
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

			for(UInt32 i = 0;  i< childs.Count(); i++)
			{
				TikiBone* tmp = childs[i]->GetBoneByIndex(index);
				if(tmp != 0)
					return tmp;
			}

			return 0;
		}

		TikiLayer& TikiBone::GetAnimationLayer(TikiAnimation* animation)
		{
			return this->animationData.GetRef(animation);
		}

		string TikiBone::GetName()
		{
			return name;
		}

		void TikiBone::SetName(string name)
		{
			this->name = name;
		}

		int TikiBone::GetConstantBufferIndex()
		{
			return this->constantBufferIndex;
		}

		void TikiBone::SetConstantBufferIndex(int index)
		{
			this->constantBufferIndex = index;
		}

		void TikiBone::AddAnimation(TikiAnimation* animation, TikiLayer& layer)
		{
			this->animationData.Add(animation, layer);
		}
		#pragma endregion

		#pragma region TikiLayer
		TikiLayer::TikiLayer()
		{
		}

		TikiLayer::~TikiLayer()
		{	 
		}

		void TikiLayer::Update(TikiAnimation* animation)
		{
			this->transformMatrix = Matrix::CreateFromQuaternion(LocalQuaternion(animation))
				* Matrix::CreateTranslation(LocalTranslation(animation));
		}

		Vector3 TikiLayer::LocalTranslation(TikiAnimation* animation)
		{
			if(animation->Left == animation->Right)
				return translation[animation->Left];
			if(animation->Right == -1)
				return translation[animation->Left];
			if(animation->Left == -1)
				return translation[animation->Right];

			return Vector3::Lerp(translation[animation->Left], translation[animation->Right], animation->Koeff);
		}

		Quaternion TikiLayer::LocalQuaternion(TikiAnimation* animation)
		{
			if(animation->Left == animation->Right)
				return quaternionen[animation->Left];
			if(animation->Right == -1)
				return quaternionen[animation->Left];
			if(animation->Left == -1)
				return quaternionen[animation->Right];

			return Quaternion::Slerp(quaternionen.Get(animation->Left), quaternionen.Get(animation->Right), animation->Koeff);

		}

		Vector3 TikiLayer::LocalTranslation(int left, int right, float koeff)
		{
			if(left == right)
				return translation[left];
			if(right == -1)
				return translation[left];
			if(left == -1)
				return translation[right];

			return Vector3::Lerp(translation[left], translation[right], koeff);
		}

		Quaternion TikiLayer::LocalQuaternion(int left, int right, float koeff)
		{
			if(left == right)
				return quaternionen[left];
			if(right == -1)
				return quaternionen[left];
			if(left == -1)
				return quaternionen[right];

			return Quaternion::Slerp(quaternionen.Get(left), quaternionen.Get(right), koeff);
		}

		Matrix TikiLayer::LocalTransform(const double& time)
		{
			return transformMatrix;
		}

		List<Vector3>& TikiLayer::GetTranslation()
		{
			return this->translation;
		}

		List<Quaternion>& TikiLayer::GetQuaternion()
		{
			return this->quaternionen;
		}
		#pragma endregion

		#pragma region TikiAnimation
		TikiAnimation::TikiAnimation()
			: Left(0), Right(0), weight(1.0f), currentTime(0.0)
		{
		}

		TikiAnimation::~TikiAnimation()
		{
		}

		string TikiAnimation::GetName()
		{
			return this->name;
		}

		void TikiAnimation::SetName(string name)
		{
			this->name = name;
		}

		List<double>& TikiAnimation::GetTimeStamps()
		{
			return this->timeStamps;
		}

		void TikiAnimation::SetTimeStamps(List<double>& timeStamps)
		{
			this->timeStamps = timeStamps;
		}

		double& TikiAnimation::GetStartTime()
		{
			return this->startTime;
		}

		double& TikiAnimation::GetStopTime()
		{
			return this->stopTime;
		}

		float TikiAnimation::GetWeight()
		{
			return this->weight;
		}

		void TikiAnimation::SetWeight(float weight)
		{
			this->weight = weight;
		}

		void TikiAnimation::AddTimeStampKey(double time)
		{
			if(timeStamps.Count() == 0)
				startTime = stopTime = time;

			if(!timeStamps.Contains(time))
			{
				timeStamps.Add(time);

				if(time < startTime)
					startTime = time;
				if(time > stopTime)
					stopTime = time;
			}
		}

		void TikiAnimation::SetBSV(int bsv)
		{
			this->bsv = bsv;
		}

		double TikiAnimation::GCurrentTime()
		{
			return this->currentTime;
		}


		void TikiAnimation::Update(const double& deltaTime)
		{
			this->currentTime += deltaTime;

			if(currentTime >= stopTime)
				currentTime -= stopTime - startTime;


			if(lastUpdateTime == currentTime)
				return;
			else
				lastUpdateTime = currentTime;

			int count = timeStamps.Count();
			//one element - always the defaultvalue
			if(count == 1)
			{
				Left = Right = 0;
				return;
			}
			//before first element -> return first element
			if(timeStamps[0] >= currentTime) 
			{
				Left = 0;
				Right = -1;
				return;
			}
			//after last element -> return last element
			if(timeStamps[count - 1] <= currentTime)
			{
				Left = -1;
				Right = count -1;
				return;
			}

			int index = 0;
			int shift = bsv;

			//find index of highest value below time
			while(shift != 0)
			{
				if(index + shift < count && timeStamps[index + shift] <= currentTime)
					index += shift;
				shift /= 2;
			}

			if(timeStamps[index] == currentTime)
			{
				Left = Right = index;
				return;
			}

			Left = index;
			Right = index + 1;

			Koeff = (float)((currentTime - timeStamps[Left]) / (timeStamps[Right] - timeStamps[Left]));
		}
		#pragma endregion
	}
}