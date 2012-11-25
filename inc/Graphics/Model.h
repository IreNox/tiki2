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

			float GetAnimationSpeed();
			void SetAnimationSpeed(float speed);

			TikiBone* GetRootBone();
			void SetRootBone(TikiBone* bone);

			List<TikiMesh*>* GetMeshes();
			void SetMeshes(List<TikiMesh*>& meshes);

			void AddAnimation(TikiAnimation* animation);
			List<TikiAnimation*>* GetAnimations();

			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

			int AnimationCount();

		private:

			void Initialize();
			void InitializeAnimation();
			void InitializeBoneMapping();

			void InitializeAnimationStack();
			void SetCurrentAnimStack(int pIndex);

			void CopyVertexData();
			void CopyIndexData();

			float animationSpeed;


			List<TikiBone*> constantBufferElements;
			List<SkinningVertex> verticesList;
			List<UInt32> indicesList;

			List<TikiMesh*> meshes;
			List<TikiAnimation*> animations;

			List<TikiAnimation*> animationStack;

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
