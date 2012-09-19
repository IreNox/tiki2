#pragma once

#include "Core/Component.h"

#include <Cloddy/Cloddy_Core.h>
#include <Cloddy/Cloddy_Kernel.h>
#include <Cloddy/Cloddy_API.h>
#include <Cloddy/Cloddy_Graphics.h>
#include <Cloddy/Cloddy_Extensions.h>

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

			TerrainRenderer(Engine* engine);
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