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
#include "Graphics/TerrainIndexBuffer.h"
#include "Graphics/TerrainVertexBuffer.h"
#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	namespace Components
	{
		using namespace Cloddy::Graphics;
		using namespace Cloddy::Extensions;
		using namespace Cloddy::API::VertexFactories::VertexFormats;
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Graphics;

		class TerrainRenderer : public ITerrainRenderer
		{
		public:

			TerrainRenderer(Engine* engine, GameObject* gameObject);
			~TerrainRenderer();

			void LoadTerrain(string fileName, int scale, int size, float elevation
#if _DEBUG
				, bool UseCloddy
#endif
			);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			Material* GetMaterial();
			void SetMaterial(Material* mat);

			int GScale() { return scale; }
			int GSize() { return size; }
			float GElevation() { return elevation; }

			float SampleHeight(const Vector3& position);

			void UpdateCollider(IHeightFieldCollider* collider);
			//void UpdateCollider(ITriangleMeshCollider* collider, List<Vector3>* poi);

#if _DEBUG
			void ToggleDrawCollider() { drawCollider = !drawCollider; }
#endif

			bool GetReady();
	
		private:

			Material* material;
			ID3D11InputLayout* layout;

			UInt32 collisionRegions;
			TerrainIndexBuffer* collisionIndexBuffer;
			TerrainVertexBuffer* collisionVertexBuffer;

			int size;
			int scale;
			float elevation;
			string fileName;

			codex_Ptr<IVertexFormat> vertexFormat;

			codex_Ptr<IndexBuffer> indexBuffer;
			codex_Ptr<VertexBuffer> vertexBuffer;

			codex_Ptr<CloddyManager> manager;
			codex_Ptr<CloddyDescription> description;

			codex_Ptr<ICloddyTerrain> terrain;
			codex_Ptr<cloddy_CloddyRectangularTerrainDescription> terrainDescription;
			codex_Ptr<CloddyLocalDataset> datasetDraw;
			codex_Ptr<CloddyLocalDataset> datasetSample;

			IHeightmap* heightmap;

			codex_Ptr<TriangulationCallback> callback;


#if _DEBUG
			bool useCloddy;
			bool drawCollider;
#endif

			CodeX::int32 toCloddyColor(Color c);

		};
	}
}