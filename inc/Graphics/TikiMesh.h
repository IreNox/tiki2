#pragma once

#include "Core/TypeGlobals.h"

#include "Core/List.h"
#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"
#include "Core/IModel.h"
#include "Graphics/TikiBone.h"

using namespace TikiEngine::Vertices;

namespace TikiEngine
{
	namespace Resources
	{

		class TikiMesh : public TikiObject
		{

		public:

			TikiMesh();
			~TikiMesh();


			void SetIndices(List<UInt32>& indices);
			void SetSkinningVertexData(List<SkinningVertex>& skinning);

			bool GetReady();

			List<SkinningVertex> verticesList;
			List<UInt32> indicesList;
			List<Matrix> skinMatrices;

			const char* GetName();
			void SetName(const char* name);

			void SetDeformation(bool b);
			bool UseDeformation();

			Material* GetMaterial();
			void SetMaterial(Material* material);

		private:

			const char* name;

			Engine* engine;

			Material* material;

			bool hasDeformation;
		};
	}
}
