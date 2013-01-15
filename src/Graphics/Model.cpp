
#include "Graphics/Model.h"
#include "Core/TypeGlobals.h"
#include "Core/IGraphics.h"
#include "Core/IContentManager.h"
#include "Core/LibraryManager.h"
#include "Core/ISpriteBatch.h"

#include "Graphics/DllMain.h"
#include "Graphics/TikiMesh.h"
#include <Core/IFont.h>
#include <Core/Engine.h>

#include "Graphics/ModelConverter.h"

namespace TikiEngine
{
	namespace Resources
	{
		#pragma region Class
		Model::Model(Engine* engine)
			: IModel(engine), rootBone(0), mainInstance(false)
		{
			constantBufferMatrices = new ConstantBuffer<SkinMatrices>(engine);

			SkinMatrices* mat = constantBufferMatrices->MapTI();
			ZeroMemory(mat, sizeof(SkinMatrices));
			constantBufferMatrices->Unmap();
		}

		Model::~Model()
		{
			SafeDelete(&constantBufferMatrices);

			for(UInt32 i = 0; i < animations.Count(); i++)
				SafeRelease(&animations[i]);

			for(UInt32 i = 0; i < meshes.Count(); i++)
				SafeRelease(&meshes[i]);

			SafeRelease(&rootBone);
		}
		#pragma endregion

		#pragma region Member - CreateInstance
		void Model::CreateInstance(IModel* model)
		{
			Model* baseModel = dynamic_cast<Model*>(model);

			SafeAddRef(baseModel->rootBone, &rootBone);

			meshes = baseModel->meshes;
			FOREACH_PTR_CALL(meshes, AddRef())

			constantBufferElements = baseModel->constantBufferElements;

			i = 0;
			while (i < baseModel->animations.Count())
			{
				animations.Add(
					new TikiAnimation(baseModel->animations[i])
				);

				i++;
			}

			if (i > 0)
			{
				animationStack.SetAnimation(animations[0]);
			}
		}
		#pragma endregion

		#pragma region Member - Get/Set
		void Model::AddAnimation(TikiAnimation* animation) //TODO ADD CURVES BLA
		{
			if(!this->animations.Contains(animation))
			{
				animation->SetIndex(animations.Count());
				this->animations.Add(animation);
			}
			if(animations.Count() == 1)
				animationStack.SetAnimation((IAnimation*)animation);
		}
		IAnimation* Model::GetAnimation(string name)
		{
			for(UInt32 i = 0; i < animations.Count(); i++)
			{
				if(animations[i]->GetName() == name)
					return (IAnimation*)animations[i];
			}
			return 0;
		}
		IAnimation* Model::GetAnimation(UInt32 index)
		{
			if(index >= 0 && index <= animations.Count())
				return (IAnimation*)animations[index];
			return 0;
		}

		void Model::SetAnimation(IAnimation* animation)
		{
			this->animationStack.SetAnimation(animation);
		}
		void Model::BlendToAnimation(IAnimation* animation, double time)
		{
			this->animationStack.BlendAnimation(animation, time);
		}

		IModelMesh* Model::GetMesh(string name)
		{
			UInt32 i = 0;
			while (i < meshes.Count())
			{
				if (meshes[i]->GetName() == name) return meshes[i];
				i++;
			}

			return 0;
		}

		IBone* Model::GetBone(string name)
		{
			if(rootBone != 0)
				return (IBone*)rootBone->GetBoneByName(name);
			return 0;
		}

		List<TikiAnimation*>* Model::GetAnimations()
		{
			return &animations;
		}

		void* Model::GetNativeResource()
		{
			return 0;
		}

		bool Model::GetReady()
		{
			return (meshes.Count() != 0);
		}

		TikiBone* Model::GetRootBone()
		{
			return this->rootBone;
		}

		void Model::SetRootBone(TikiBone* bone)
		{
			if(this->rootBone != 0)
				SafeRelease(&rootBone);
			rootBone = bone;
			rootBone->AddRef();
		}

		void Model::SetConstantBufferIndices(List<TikiBone*>& list)
		{
			this->constantBufferElements = list;
		}

		int Model::AnimationCount()
		{
			return this->animations.Count();
		}

		List<TikiMesh*>* Model::GetMeshes()
		{
			return &meshes;
		}

		void Model::SetMeshes(List<TikiMesh*>& meshes)
		{
			this->meshes = meshes;
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void Model::Draw(GameObject* gameObject, const DrawArgs& args)
		{
#if _DEBUG
			if (!this->GetReady())
			{
				throw "Model don't ready.";
			}
#endif

			UInt32 i = 0;
			while (i < meshes.Count())
			{
				meshes[i]->Draw(args, this, gameObject);
				i++;
			}

#if _DEBUG
			//args.Graphics->DrawLine(Vector3(), Vector3(3.0f,0.0f,0.0f), Color::Red);
			//args.Graphics->DrawLine(Vector3(), Vector3(0.0f,3.0f,0.0f), Color::Green);
			//args.Graphics->DrawLine(Vector3(), Vector3(0.0f,0.0f,3.0f), Color::Blue);

			//rootBone->Draw(args);
#endif
		}

		void Model::Update(const UpdateArgs& args)
		{
#if _DEBUG
			if (!this->GetReady())
			{
				throw "Model don't ready.";
			}
#endif

			this->animationStack.Update(args);
		}

		void Model::LateUpdate(const UpdateArgs& args)
		{
			if(this->rootBone != 0)
				rootBone->Update(this->animationStack.GetStack());

			SkinMatrices* matrices = constantBufferMatrices->MapTI();
			int matrixCount = this->constantBufferElements.Count();
			for(int i = 0; i < matrixCount; i++)
			{
				TikiBone* b = constantBufferElements[i];
				matrices->bones[i] = this->constantBufferElements[i]->ShiftMatrix();
			}
			constantBufferMatrices->Unmap();
		}
		#pragma endregion

		#pragma region Protected Member
		void Model::loadFromStream(wcstring fileName, Stream* stream)
		{
			mainInstance = true;

			ModelConverter* convert = new ModelConverter(this, stream);
			delete(convert);
			
			FOREACH_PTR_CALL(meshes, AddRef())

			UpdateArgs args = UpdateArgs();
			this->Update(args);
		}

		void Model::saveToStream(wcstring fileName, Stream* stream)
		{
			ModelConverter* convert = new ModelConverter(this);
			convert->WriteToStream(stream);
			delete(stream);
		}
		#pragma endregion
	}
}
