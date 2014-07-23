#pragma once

#include "Core/ITerrainRenderer.h"

//#include "Graphics/TikiHeightmap.h"
//#include "Graphics/TerrainIndexBuffer.h"
//#include "Graphics/TerrainVertexBuffer.h"
//#include "Graphics/TerrainTriangulationCallback.h"

#include "Graphics/VertexDeclaration.h"
#include "Graphics/StaticBuffer.h"

namespace TikiEngine
{
	struct TerrainVertex;

	namespace Components
	{
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Graphics;

		class TerrainRenderer : public ITerrainRenderer
		{
		public:

			TerrainRenderer(Engine* engine, GameObject* gameObject);
			~TerrainRenderer();

			void LoadTerrain(string fileName, int scale, int size, float elevation, bool useCloddy );

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			Material* GetMaterial();
			void SetMaterial(Material* mat);

			int GScale() { return scale; }
			int GSize() { return size; }
			float GElevation() { return elevation; }

			float SampleHeight(const Vector3& position);

			bool GetReady();
	
		private:

			Material* material;

			TDX_InputLayout* layout;

			TerrainVertex*		m_pVertexData;
			int					m_vertexCount;

			StaticBuffer< TIKI_VERTEX_BUFFER >*	m_pVertexBuffer;

			bool useCloddy;

			int size;
			int scale;
			float elevation;
			string fileName;

//			codex_Ptr<IVertexFormat> vertexFormat;
//
//			//TerrainIndexBuffer* indexBuffer;
//			//TerrainVertexBuffer* vertexBuffer;
//			//TerrainTriangulationCallback* callback;
//
//			codex_Ptr<IndexBuffer> indexBuffer;
//			codex_Ptr<VertexBuffer> vertexBuffer;
//			codex_Ptr<TriangulationCallback> callback;
//
//			codex_Ptr<CloddyManager> manager;
//			codex_Ptr<CloddyDescription> description;
//
//			codex_Ptr<ICloddyTerrain> terrain;
//			codex_Ptr<cloddy_CloddyRectangularTerrainDescription> terrainDescription;
//			codex_Ptr<CloddyLocalDataset> datasetDraw;
//			codex_Ptr<CloddyLocalDataset> datasetSample;
//
//			IHeightmap* heightmap;
//
//			CodeX::int32 toCloddyColor(Color c);

		};
	}
}