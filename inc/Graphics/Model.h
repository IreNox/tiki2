#pragma once

#include "Core/List.h"
#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"
#include "Core/IModel.h"

#include "Graphics/TikiMesh.h"
#include "Graphics/DynamicBuffer.h"
#include "Graphics/StaticBuffer.h"
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

			void* GetNativeResource();

			void Draw(GameObject* gameObject, const DrawArgs& args);
			void Update(const UpdateArgs& args);

			Material* GetMaterial();
			void SetMaterial(Material* material);

			List<SkinningVertex>* GetVertices();
			List<UInt32>* GetIndices();

			void SetConstantBufferIndices(List<TikiBone*>& list);


			TikiBone* GetRootBone();
			void SetRootBone(TikiBone* bone);

			List<TikiMesh*>* GetMeshes();
			void SetMeshes(List<TikiMesh*>& meshes);

			void AddAnimation(TikiAnimation* animation);
			List<TikiAnimation*>* GetAnimations();

			bool GetReady();

			IAnimation* GetAnimation(string name);
			IAnimation* GetAnimation(int index);

			void SetAnimation(IAnimation* animation);
			void BlendToAnimation(IAnimation* animation, double time = 0.5);

			IBone* GetBone(string name);

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

			int AnimationCount();

		private:

			void Initialize();

			void CopyVertexData();
			void CopyIndexData();


			List<TikiBone*> constantBufferElements;
			List<SkinningVertex> verticesList;
			List<UInt32> indicesList;

			List<TikiMesh*> meshes;
			List<TikiAnimation*> animations;

			AnimationStack animationStack;
			//List<TikiAnimation*> animationStack;

			Material* material;
			VertexDeclaration* declaration;

			StaticBuffer<D3D11_BIND_INDEX_BUFFER>* indexBuffer;
			StaticBuffer<D3D11_BIND_VERTEX_BUFFER>* vertexBuffer;


			SkinMatrices matrices;
			ConstantBuffer<SkinMatrices>* constantBufferMatrices;

			TikiBone* rootBone;

		};
	}
}
