#include "Graphics/AnimationStack.h"
#include "Graphics/ModelConverter.h"

#ifdef TIKI_ENGINE
#include "Core/IContentManager.h"

#include "Graphics/Model.h"
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
#ifdef TIKI_ENGINE
			TikiMesh* mesh = new TikiMesh(
				model->GetEngine()
			);
#else
			TikiMesh* mesh = new TikiMesh();
#endif

			mesh->SetName(readString(binMesh->NameId));
			mesh->SetDeformation(binMesh->UseDeformation != 0);
			mesh->SetAdjacencyIndices(binMesh->HasAdjacencyIndices != 0);

#ifdef TIKI_ENGINE
			if (binMesh->UseDeformation)
			{
				mesh->SetMaterial(model->GetEngine()->content->LoadMaterial(L"os_skinning"));
			}
			else
			{
				mesh->SetMaterial(model->GetEngine()->content->LoadMaterial(L"os_default"));
			}

			mesh->GetMaterial()->TexDiffuse     = readTexture(binMesh->DiffuseTexId);
			mesh->GetMaterial()->TexLightMap    = readTexture(binMesh->LightTexId);
			mesh->GetMaterial()->TexNormalMap   = readTexture(binMesh->NormalTexId);
			mesh->GetMaterial()->TexSpecularMap = readTexture(binMesh->SpecTexId);
#endif

			BinaryPart& dataPart = context->ReadPart(binMesh->VertexDataId);			
			mesh->SetVertexData(
				(SkinningVertex*)context->ReadPartPointer(dataPart.Id),
				dataPart.ArrayCount * dataPart.Length
			);
			
			dataPart = context->ReadPart(binMesh->IndexDataId);
			mesh->SetIndexData(
				(UInt32*)context->ReadPartPointer(dataPart.Id),
				dataPart.ArrayCount
			);

			if (mesh->HasAdjacencyIndices())
			{
				dataPart = context->ReadPart(binMesh->AdjacencyIndexDataId);
				mesh->SetAdjacencyIndexData(
					(UInt32*)context->ReadPartPointer(dataPart.Id),
					dataPart.ArrayCount
				);
			}

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

		ITexture* ModelConverter::readTexture(UInt32 id)
		{
#ifdef TIKI_ENGINE
			if (id == 0) return 0;

			wstring fileName = StringAtoW(readString(id));

			return model->GetEngine()->content->LoadTexture(fileName);
#else
			return 0;
#endif
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
			btm->NameId = addPartsString(mesh->GetName());
			btm->UseDeformation = mesh->UseDeformation();
			btm->HasAdjacencyIndices = mesh->HasAdjacencyIndices();

			UInt32 indexCount;
			UInt32* indexData;
			mesh->GetIndexData(&indexData, &indexCount);

			UInt32 vertexLength;
			void* vertexData;
			mesh->GetVertexData(&vertexData, &vertexLength);

			btm->VertexDataId = context->AddPart(vertexData, sizeof(SkinningVertex), PT_Array, PT_Byte, vertexLength / sizeof(SkinningVertex));
			btm->IndexDataId = context->AddPart(indexData, sizeof(UInt32), PT_Array, PT_UInt, indexCount);

			if (btm->HasAdjacencyIndices)
			{
				mesh->GetAdjacencyIndexData(&indexData, &indexCount);
				btm->AdjacencyIndexDataId = context->AddPart(indexData, sizeof(UInt32), PT_Array, PT_UInt, indexCount);
			}
			else
			{
				btm->AdjacencyIndexDataId = 0;
			}

			Material* mat = mesh->GetMaterial();

			if (mat != 0)
			{
				btm->DiffuseTexId = addPartsTexture(mat->TexDiffuse);
				btm->LightTexId   = addPartsTexture(mat->TexLightMap);
				btm->NormalTexId  = addPartsTexture(mat->TexNormalMap);
				btm->SpecTexId    = addPartsTexture(mat->TexSpecularMap);
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

				return addPartsString(name);
			}

			return 0;
		}

		UInt32 ModelConverter::addPartsBone(TikiBone* bone, UInt32 parentId)
		{
			BinaryTikiBone* btb = new BinaryTikiBone();
			btb->NameId = addPartsString(bone->GetName());
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
						&bone->GetAnimationLayer(i)
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
			bta->NameId = addPartsString(animation->GetName());

			bta->StartTime = animation->GetStartTime();
			bta->EndTime = animation->GetStopTime();

			bta->BSV = animation->GetBSV();

			bta->TimeStampsArrayId = context->AddPart((void*)animation->GetTimeStamps().GetInternalData(), sizeof(double), PT_Array, PT_Double, animation->GetTimeStamps().Count());

			animationIds.Add(
				context->AddPart(bta, sizeof(BinaryTikiAnimation), PT_Animation)
			);
		}

		UInt32 ModelConverter::addPartsString(string str)
		{
			UInt32 len = (UInt32)str.size() + 1;
			char* str2 = new char[len];
			memcpy(str2, str.c_str(), len);

			return context->AddPart(str2, len, PT_String);
		}
		#pragma endregion
		#pragma endregion

		#pragma region TikiMesh
		#pragma region Class
#ifdef TIKI_ENGINE
		TikiMesh::TikiMesh(Engine* engine)
			: EngineObject(engine), indexBuffer(0), vertexBuffer(0), decl(0),
#else
		TikiMesh::TikiMesh()
			: EngineObject(0),
#endif
			  material(0), hasDeformation(false), indexData(0), vertexData(0), indexCount(0), vertexLength(0), adjacencyIndexData(0), adjacencyIndexCount(0)
		{
		}

		TikiMesh::~TikiMesh()
		{
			SafeDeleteArray(&indexData);
			SafeDeleteArray(&adjacencyIndexData);
			SafeDeleteArray(&vertexData);

#ifdef TIKI_ENGINE
			SafeRelease(&decl);
			SafeRelease(&indexBuffer);
			SafeRelease(&indexAdjacencyBuffer);
			SafeRelease(&vertexBuffer);
#endif

			SafeRelease(&material);
		}
		#pragma endregion
		
		#pragma region Member - Draw
		void TikiMesh::Draw(const DrawArgs& args, Model* model, GameObject* gameObject)
		{
#ifdef TIKI_ENGINE
			if (!this->GetReady()) return;

			material->GetShader()->SelectSubByIndex(args.Mode);
			material->UpdateDrawArgs(args, gameObject);
			material->Apply();

			if (hasDeformation)
			{
				material->GetShader()->SetConstantBuffer("SkinMatrices", model->GetConstantBuffer());
			}

			decl->Apply();
			vertexBuffer->Apply();
			(args.Mode == DM_Shadows || true ? indexAdjacencyBuffer : indexBuffer)->Apply();

			if (args.Mode == DM_Shadows || true)
			{
				if (!hasAdjacencyIndices) return;
				
				DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ);
				DllMain::Context->DrawIndexed(adjacencyIndexCount, 0, 0);
			}
			else
			{
				DllMain::Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				DllMain::Context->DrawIndexed(indexCount, 0, 0);
			}
#endif
		}
		#pragma endregion

		#pragma region Member - Get/Set
		Material* TikiMesh::GetMaterial()
		{
			return material;
		}

		void TikiMesh::SetMaterial(Material* material)
		{
			SafeRelease(&this->material);
			SafeAddRef(material, &this->material);

#ifdef TIKI_ENGINE
			if (material)
			{
				SafeRelease(&decl);
				decl = new VertexDeclaration(engine, material->GetShader(), SkinningVertex::Declaration, SkinningVertex::DeclarationCount);
			}
#endif
		}

		bool TikiMesh::GetReady()
		{
			return indexData != 0 && vertexData != 0 && material != 0;
		}
		#pragma endregion

		#pragma region Member - Get/Set - Indices/Vertices
		void TikiMesh::GetIndexData(UInt32** data, UInt32* count)
		{
			*data = indexData;
			*count = indexCount;
		}

		void TikiMesh::SetIndexData(const UInt32* data, UInt32 count)
		{
			SafeDeleteArray(&indexData);
			indexData = new UInt32[count];
			indexCount = count;

			memcpy(indexData, data, sizeof(UInt32) * count);

#ifdef TIKI_ENGINE
			indexBuffer = new StaticBuffer<D3D11_BIND_INDEX_BUFFER>(engine, sizeof(UInt32), count, indexData);
#endif
		}

		void TikiMesh::GetAdjacencyIndexData(UInt32** data, UInt32* count)
		{
			*data = adjacencyIndexData;
			*count = adjacencyIndexCount;
		}

		void TikiMesh::SetAdjacencyIndexData(const UInt32* data, UInt32 count)
		{
			SafeDeleteArray(&adjacencyIndexData);
			adjacencyIndexData = new UInt32[count];
			adjacencyIndexCount = count;

			memcpy(adjacencyIndexData, data, sizeof(UInt32) * count);

#ifdef TIKI_ENGINE
			indexAdjacencyBuffer = new StaticBuffer<D3D11_BIND_INDEX_BUFFER>(engine, sizeof(UInt32), count, adjacencyIndexData);
#endif
		}

		void TikiMesh::GetVertexData(void** data, UInt32* length)
		{
			*data = vertexData;
			*length = vertexLength;
		}

		void TikiMesh::SetVertexData(const void* data, UInt32 length)
		{
			SafeDeleteArray(&vertexData);
			vertexData = new Byte[length];
			vertexLength = length;

			memcpy(vertexData, data, length);

#ifdef TIKI_ENGINE
			vertexBuffer = new StaticBuffer<D3D11_BIND_VERTEX_BUFFER>(engine, sizeof(SkinningVertex), length / sizeof(SkinningVertex), vertexData);
#endif
		}
		#pragma endregion
		#pragma endregion

		#pragma region TikiBone
		TikiBone::TikiBone()
			:parent(0), childs(), boneInit(), boneInitInverse(), boneCurrent(), constantBufferIndex(-1), ignoreUpdate(false)
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

		void TikiBone::Draw(const DrawArgs& args)
		{
			for(UInt32 i = 0; i < childs.Count(); i++)
				childs[i]->Draw(args);
		}

		void TikiBone::Update(List<TikiAnimation*>& animations)
		{
			if(ignoreUpdate)
				return;

			Matrix shift;
			int animationCount = animations.Count();

			if(animationCount == 1)
			{
				TikiAnimation* anim = animations[0];
				TikiLayer& layer = animationData[anim->GetIndex()];
				layer.Update(anim);

				shift = layer.LocalTransform();
			}
			else
			{
				TikiAnimation* anim1 = animations[0];
				TikiLayer& layer1 = animationData[anim1->GetIndex()];
				layer1.Update(anim1);

				Quaternion quat = layer1.LocalQuaternion();
				Vector3 trans = layer1.LocalTranslation();
				float weight = anim1->GetWeight();

				for(int i = 1; i < animationCount; i++)
				{
					TikiAnimation* anim2 = animations[i];
					TikiLayer& layer2 = animationData[anim2->GetIndex()];
					layer2.Update(anim2);

					float koeff = 1 -(weight / (weight + anim2->GetWeight()));

					quat = Quaternion::Slerp(quat, layer2.LocalQuaternion(), koeff);
					trans = Vector3::Lerp(trans, layer2.LocalTranslation(), koeff);

					weight += anim2->GetWeight();
				}

				shift = Matrix::CreateFromQuaternion(quat) * Matrix::CreateTranslation(trans);
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

		Vector3 TikiBone::Position()
		{
			return Vector3::TransformCoordinate(Vector3(), this->boneCurrent);
		}

		Vector3 TikiBone::Forward()
		{
			if(this->parent == 0)
				return Vector3::One;
			else
			{
				return Vector3::Normalize(this->Position() - this->GetParent()->Position());
			}
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

		TikiBone* TikiBone::GetBoneByName(const string& name)
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

			for(UInt32 i = 0;  i< childs.Count(); i++)
			{
				TikiBone* tmp = childs[i]->GetBoneByIndex(index);
				if(tmp != 0)
					return tmp;
			}

			return 0;
		}

		TikiLayer& TikiBone::GetAnimationLayer(UInt32 index)
		{
			return this->animationData[index];
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

		void TikiBone::IgnoreUpdate(bool b)
		{
			this->ignoreUpdate = b;
		}

		void TikiBone::AddAnimation(TikiAnimation* animation, TikiLayer& layer)
		{
			this->animationData.Add(/*animation, */layer);
		}
		#pragma endregion

		#pragma region TikiLayer
		TikiLayer::TikiLayer()
			: currentTranslation(), currentQuaternion()
		{
		}

		TikiLayer::~TikiLayer()
		{	 
		}

		void TikiLayer::Update(TikiAnimation* animation)
		{
			this->currentTranslation = LocalTranslation(animation);
			this->currentQuaternion = LocalQuaternion(animation);

			this->transformMatrix = Matrix::CreateFromQuaternion(this->currentQuaternion)
				 * Matrix::CreateTranslation(currentTranslation);
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

		Vector3& TikiLayer::LocalTranslation()
		{
			return this->currentTranslation;
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

		
		Quaternion& TikiLayer::LocalQuaternion()
		{
			return this->currentQuaternion;
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
			: Left(0), Right(0), weight(1.0f), currentTime(0.0), animationSpeed(1.0f), isLoop(true), finished(false), nextAnimation(0)
		{
		}

		TikiAnimation::TikiAnimation(TikiAnimation* copy)
			: Left(copy->Left), Right(copy->Right), weight(copy->weight), animationSpeed(copy->animationSpeed), isLoop(copy->isLoop),
			  finished(copy->finished), nextAnimation(copy->nextAnimation), name(copy->name), index(copy->index), bsv(copy->bsv),
			  startTime(copy->startTime), stopTime(copy->stopTime), lastUpdateTime(copy->lastUpdateTime), currentTime(copy->currentTime)
		{
			timeStamps = copy->timeStamps;

#if _DEBUG
			if (nextAnimation != 0)
				throw "Not implemented Exception";
#endif
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

		int TikiAnimation::GetIndex()
		{
			return this->index;
		}

		void TikiAnimation::SetIndex(int index)
		{
			this->index = index;
		}

		double TikiAnimation::GetDuration()
		{
			return (this->stopTime - this->startTime) * this->animationSpeed;
		}

		void TikiAnimation::SetDuration(double time)
		{
			this->animationSpeed = (float)((this->stopTime - this->startTime) / time);
		}

		double TikiAnimation::GetAnimationSpeed()
		{
			return this->animationSpeed;
		}
		void TikiAnimation::SetAnimationSpeed(double speed)
		{
			this->animationSpeed = (float)speed;
		}

		bool TikiAnimation::GetLoop()
		{
			return this->isLoop;
		}
		
		void TikiAnimation::SetLoop(bool isLoop)
		{
			this->isLoop = isLoop;
		}

		bool TikiAnimation::IsFinished()
		{
			return this->finished;
		}

		void TikiAnimation::SetNextAnimation(IAnimation* animation)
		{
			this->nextAnimation = animation;
		}

		IAnimation* TikiAnimation::GetNextAnimation()
		{
			return this->nextAnimation;
		}

		void TikiAnimation::Reset()
		{
			this->currentTime = this->startTime;
			this->finished = false;
			this->Update();
		}

		void TikiAnimation::Update(const double& deltaTime)
		{
			if(finished)
				return;

			this->currentTime += deltaTime * this->animationSpeed;

			if(currentTime >= stopTime)
			{
				if(!isLoop)
					finished = true;

				currentTime -= stopTime - startTime;
			}


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

		#pragma region AnimationStack
		AnimationStack::AnimationStack()
			: blendTarget(0)
		{

		}

		AnimationStack::~AnimationStack()
		{
			
		}

		void AnimationStack::Update(const UpdateArgs& args)
		{
			this->blend(args);

			for(UInt32 i = 0; i < this->stack.Count(); i++)
			{
				TikiAnimation* anim = stack[i];
				if(anim == blendTarget)
					continue;

				anim->Update(args.Time.ElapsedTime);
			}
		}

		void AnimationStack::SetAnimation(IAnimation* animation)
		{
//#if _DEBUG
//			if(animation == 0) 
//				_CrtDbgBreak();
//#endif
			this->stack.Clear();

			if (animation != 0)
			{
				animation->Reset();
				animation->SetWeight(1.0);
				this->stack.Add((TikiAnimation*)animation);
			}
		}

		void AnimationStack::BlendAnimation(IAnimation* animation, double time)
		{
			if(blendTarget == animation)
				return;

#if _DEBUG
			if(animation == 0)
				_CrtDbgBreak();
#endif
			
			if(stack.Contains((TikiAnimation*)animation))
			{
				blendTarget = (TikiAnimation*)animation;
				blendTimer = time;
				blendTime = blendTimer * blendTarget->GetWeight();
				return;
			}

			this->blendTarget = (TikiAnimation*)animation;
			this->blendTarget->Reset();
			this->blendTarget->SetWeight(0.0);
			this->blendTimer = time;
			this->blendTime = 0;

			this->stack.Add(blendTarget);
		}

		List<TikiAnimation*>& AnimationStack::GetStack()
		{
			return this->stack;
		}

		void AnimationStack::blend(const UpdateArgs& args)
		{
			if(blendTarget == 0)
				return;

			float lastWeight = blendTarget->GetWeight();

			this->blendTime += args.Time.ElapsedTime;
			
			if(blendTime >= blendTimer)
			{
				stack.Clear();
				blendTarget->SetWeight(1.0);
				stack.Add(blendTarget);
				blendTarget = 0;
				return;
			}

			float currWeight = (float)(blendTime / blendTimer);
			blendTarget->SetWeight(currWeight);

			lastWeight = 1 - lastWeight;
			currWeight = 1 - currWeight;

			for(UInt32 i = 0; i < stack.Count(); i++)
			{
				TikiAnimation* anim = stack[i];
				if(blendTarget == anim)
					continue;

				anim->SetWeight(currWeight * anim->GetWeight() / lastWeight);
			}
		}

		#pragma endregion
	}
}
