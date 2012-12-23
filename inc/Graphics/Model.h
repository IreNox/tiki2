#pragma once

#include "Core/List.h"
#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"
#include "Core/IModel.h"

#include "Graphics/TikiMesh.h"
#include "Graphics/DynamicBuffer.h"
#include "Graphics/VertexDeclaration.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/SkinMatrices.h"

#include "Graphics/TikiBone.h"
#include "Graphics/TikiAnimation.h"

#include "Graphics/AnimationStack.h"

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Graphics;

		class Model : public IModel
		{
		public:

			Model(Engine* engine);
			~Model();

			void CreateInstance(IModel* model);

			void Draw(GameObject* gameObject, const DrawArgs& args);
			void Update(const UpdateArgs& args);

			void SetConstantBufferIndices(List<TikiBone*>& list);
			
			IBone* GetBone(string name);
			TikiBone* GetRootBone();
			void SetRootBone(TikiBone* bone);

			List<TikiMesh*>* GetMeshes();
			void SetMeshes(List<TikiMesh*>& meshes);

			void AddAnimation(TikiAnimation* animation);
			List<TikiAnimation*>* GetAnimations();

			IAnimation* GetAnimation(string name);
			IAnimation* GetAnimation(UInt32 index);
			void SetAnimation(IAnimation* animation);
			
			inline ConstantBuffer<SkinMatrices>* GetConstantBuffer()
			{
				return constantBufferMatrices;
			}
			void BlendToAnimation(IAnimation* animation, double time = 0.5);

			void* GetNativeResource();
			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

			int AnimationCount();

		private:

			bool mainInstance;

			TikiBone* rootBone;
			
			List<TikiMesh*> meshes;
			List<TikiAnimation*> animations;
			List<TikiBone*> constantBufferElements;

			AnimationStack animationStack;

			SkinMatrices matrices;
			ConstantBuffer<SkinMatrices>* constantBufferMatrices;

		};
	}
}
