#pragma once

#include "Core/List.h"
#include "Core/DefaultVertex.h"
#include "Core/IModel.h"

#define FBXSDK_NEW_API
#include "fbxsdk.h"

using namespace TikiEngine::Vertices;

namespace TikiEngine
{
	namespace Resources
	{
		class Model : public IModel
		{
		public:

			Model(Engine* engine);
			~Model();

			void* GetNativeResource();

			bool GetIndexData(UInt32** indices, UInt32* count);
			void SetIndexData(UInt32* indices, UInt32 count);

			bool GetVertexData(void** vertices, UInt32* size);
			void SetVertexData(void* vertices, UInt32 size);

			bool GetReady();

		protected:

			void loadFromStream(wcstring fileName, Stream* stream);
			void saveToStream(wcstring fileName, Stream* stream);

		private:

			void Initialize();
			void FillData();

			void InitializeAnimationStack();
			bool SetCurrentAnimStack(int pIndex);

			void HandleNodeRecursive(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer, FbxAMatrix& parentGlobalPosition, FbxPose* pose);
			void HandleNode(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer, FbxAMatrix& parentGlobalPosition, FbxAMatrix& globalPosition, FbxPose* pose);
			void HandleSkeleton(FbxNode* node, FbxAMatrix& parentGlobalPosition, FbxAMatrix& globalPosition);
			void HandleMesh(FbxNode* node, FbxTime& time, FbxAnimLayer* animLayer,
				FbxAMatrix& globalPosition, FbxPose* pose);

			FbxAMatrix& GetGlobalPosition(FbxNode* node, FbxTime pTime=FBXSDK_TIME_INFINITE);
			FbxAMatrix& GetGeometry(FbxNode* node);

			List<DefaultVertex> verticesList;
			List<UInt32> indicesList;

			UInt32* indices;
			void* vertices;

			UInt32 indicesCount;
			UInt32 verticesSize;

			FbxArray<FbxString*> animStackNameArray;
			FbxAnimLayer* currentAnimLayer;
			
			FbxScene* scene;

		};
	}
}