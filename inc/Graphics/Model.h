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

#define FBXSDK_NEW_API
#include "fbxsdk.h"

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

			float GetAnimationSpeed();
			void SetAnimationSpeed(float speed);

			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

			void Initialize();

			void InitializeAnimationStack();
			bool SetCurrentAnimStack(int pIndex);


			void InitializeNodeRecursive(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer, FbxAMatrix& parentGlobalPosition, FbxPose* pose);
			void InitializeNode(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer, FbxAMatrix& parentGlobalPosition, FbxAMatrix& globalPosition, FbxPose* pose);
			void InitializeMesh(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer,
				FbxAMatrix& globalPosition, FbxPose* pose);

			void CopyVertexData();
			void CopyIndexData();

			FbxAMatrix& GetGlobalPosition(FbxNode* node, FbxTime pTime=FBXSDK_TIME_INFINITE);
			FbxAMatrix GetGeometry(FbxNode* node);
			

			FbxTime start;
			FbxTime stop;
			FbxTime frameTime;
			FbxTime currentTime;
			float animationSpeed;

			double startTime;
			double stopTime;
			double timer;


			List<SkinningVertex> verticesList;
			List<UInt32> indicesList;

			List<TikiMesh*> meshes;

			Material* material;
			VertexDeclaration* declaration;

			StaticBuffer<D3D11_BIND_INDEX_BUFFER>* indexBuffer;
			StaticBuffer<D3D11_BIND_VERTEX_BUFFER>* vertexBuffer;

			UInt32 updateCounter;
			//List<UpdateStructure> updateStructure;

			FbxArray<FbxString*> animStackNameArray;
			FbxAnimLayer* currentAnimLayer;
			
			FbxScene* scene;

			SkinMatrices matrices;
			ConstantBuffer<SkinMatrices>* constantBufferMatrices;

		};
	}
}
