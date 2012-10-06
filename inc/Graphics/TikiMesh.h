#pragma once

#include "Core/TypeGlobals.h"

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
		struct UpdateStructure
		{
			int VertexIndex;
			int UVIndex;
			int NormalIndex;
		};

		class TikiMesh
		{

		public:

			TikiMesh(Engine* engine, FbxNode* node);
			~TikiMesh();

			bool Initialize();

			void Update(FbxTime& time, FbxAnimLayer* animLayer, FbxPose* pose);

			bool GetReady();

			bool GetIndexData(UInt32** indices, UInt32* count);
			void SetIndexData(UInt32* indices, UInt32 count);

			bool GetVertexData(void** vertices, UInt32* size);
			void SetVertexData(void* vertices, UInt32 size);

			void Release();

			List<DefaultVertex> verticesList;
			List<UInt32> indicesList;

		private:

			void CopyData();

			FbxNode* node;
			FbxAMatrix* matrix;
			Engine* engine;


			List<UpdateStructure> updateStructure;

			bool hasDeformation;

			UInt32* indices;
			void* vertices;

			UInt32 indicesCount;
			UInt32 verticesSize;

		};
	}
}
