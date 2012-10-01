#pragma once

#define CODEX_PREFIX
#define CLODDY_CORE_PREFIX
#define CLODDY_KERNEL_PREFIX
#define CLODDY_API_PREFIX
#define CLODDY_GRAPHICS_PREFIX
#define CLODDY_EXTENSIONS_PREFIX

#include <CodeX/Codex.h>
#include "Cloddy/Cloddy_Core.h"
#include "Cloddy/Cloddy_Kernel.h"
#include "Cloddy/Cloddy_API.h"
#include "Cloddy/Cloddy_Graphics.h"
#include "Cloddy/Cloddy_Extensions.h"

#include "Core/ITerrainRenderer.h"
#include "Graphics/TikiHeightmap.h"
#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	namespace Components
	{
		using namespace Cloddy::Graphics;
		using namespace Cloddy::Extensions;
		using namespace Cloddy::API::VertexFactories::VertexFormats;
		using namespace TikiEngine::Vertices;

		class TerrainRenderer : public ITerrainRenderer
		{
		public:

			TerrainRenderer(Engine* engine, GameObject* gameObject);
			~TerrainRenderer();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			Material* GetMaterial();
			void SetMaterial(Material* mat);

			bool GetReady();
	
		private:

			Material* material;
			ID3D11InputLayout* layout;

			codex_Ptr<IVertexFormat> vertexFormat;

			codex_Ptr<IndexBuffer> indexBuffer;
			codex_Ptr<VertexBuffer> vertexBuffer;

			codex_Ptr<CloddyManager> manager;
			codex_Ptr<CloddyDescription> description;

			codex_Ptr<TikiHeightmap> heightmap;

			codex_Ptr<ICloddyTerrain> terrain;
			codex_Ptr<cloddy_CloddyRectangularTerrainDescription> terrainDescription;
			codex_Ptr<CloddyLocalDataset> datasetElevation;
			codex_Ptr<CloddyLocalDataset> datasetDetail;
			codex_Ptr<CloddyLocalDataset> datasetColor;

			codex_Ptr<TriangulationCallback> callback;

		};
	}
}