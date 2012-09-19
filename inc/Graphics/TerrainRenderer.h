#pragma once

#include "Core/Component.h"

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

namespace TikiEngine
{
	namespace Components
	{
		using namespace Cloddy::Graphics;
		using namespace Cloddy::Extensions;
		using namespace Cloddy::API::VertexFactories::VertexFormats;

		class TerrainRenderer : public Component
		{
		public:

			TerrainRenderer(Engine* engine, GameObject* gameObject);
			~TerrainRenderer();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			bool GetReady();
	
		private:

			IVertexFormat* vertexformat;

			IndexBuffer* indexbuffer;
			VertexBuffer* vertexBuffer;

			CloddyManager* manager;
			CloddyDescription description;

			ICloddyTerrain* terrain;
			CloddySphericalTerrainDescription terrainDescription;
			CloddyLocalDataset* datasetElevation;
			CloddyLocalDataset* datasetDetail;
			CloddyLocalDataset* datasetColor;

		};
	}
}