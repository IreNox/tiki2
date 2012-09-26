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

namespace TikiEngine
{
	namespace Components
	{
		using namespace Cloddy::Graphics;
		using namespace Cloddy::Extensions;
		using namespace Cloddy::API::VertexFactories::VertexFormats;

		class TerrainRenderer : public ITerrainRenderer
		{
		public:

			TerrainRenderer(Engine* engine, GameObject* gameObject);
			~TerrainRenderer();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			bool GetReady();
	
		private:

			codex_Ptr<IVertexFormat> vertexFormat;

			codex_Ptr<IndexBuffer> indexBuffer;
			codex_Ptr<VertexBuffer> vertexBuffer;

			codex_Ptr<CloddyManager> manager;
			CloddyDescription description;

			codex_Ptr<TikiHeightmap> heightmap;

			codex_Ptr<ICloddyTerrain> terrain;
			CloddySphericalTerrainDescription terrainDescription;
			codex_Ptr<CloddyLocalDataset> datasetElevation;
			codex_Ptr<CloddyLocalDataset> datasetDetail;
			codex_Ptr<CloddyLocalDataset> datasetColor;

			codex_Ptr<TriangulationCallback> callback;

		};
	}
}