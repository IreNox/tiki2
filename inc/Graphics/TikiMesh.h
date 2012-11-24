#pragma once

#include "Core/TypeGlobals.h"

#include "Core/List.h"
#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"
#include "Core/IModel.h"
#include "Graphics/TikiBone.h"

#define FBXSDK_NEW_API
#include "fbxsdk.h"

using namespace TikiEngine::Vertices;

namespace TikiEngine
{
	namespace Resources
	{
		struct UpdateStructure
		{
			UpdateStructure(){}

			UpdateStructure(int vertexIndex, int uvIndex, int normalIndex)
			{
				VertexIndex = vertexIndex;
				UVIndex = uvIndex;
				NormalIndex = normalIndex;

				for(int i = 0; i < MAXBONESPERVERTEX; i++)
				{
					Weights[i] = -1;
					Indices[i] = 0;
				}
			}

			int VertexIndex;
			int UVIndex;
			int NormalIndex;
			float Weights[MAXBONESPERVERTEX];
			float Indices[MAXBONESPERVERTEX];
		};


		class TikiMesh : public TikiObject
		{

		public:

			TikiMesh(Engine* engine, FbxNode* node);
			~TikiMesh();

			bool Initialize();
			void InitializeGPUSkinning();
			void FlagBones(TikiBone& rootBone);
			void MapBones(TikiBone& rootBone);

			void UpdateVertexBuffer();

			bool GetReady();

			List<SkinningVertex> verticesList;
			List<UInt32> indicesList;
			List<Matrix> skinMatrices;

			bool UseDeformation()
			{
				return hasDeformation;
			}

			Material* GetMaterial()
			{
				return material;
			}

		private:
			int MaxBonesPerVertex();

			FbxNode* node;
			Engine* engine;

			Material* material;

			List<UpdateStructure> updateStructure;

			bool hasDeformation;
		};
	}
}
