#pragma once

#include "Core/ITerrainRenderer.h"

//#include "Graphics/TikiHeightmap.h"
//#include "Graphics/TerrainIndexBuffer.h"
//#include "Graphics/TerrainVertexBuffer.h"
//#include "Graphics/TerrainTriangulationCallback.h"

#include "Graphics/StaticBuffer.h"
#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	struct TerrainVertex;

	namespace Resources
	{
		class Texture;
	}

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

			VertexDeclaration*	m_pDeclaration;

			TerrainVertex*		m_pVertexData;
			UInt32				m_vertexCount;

			UInt32*				m_pIndexData;
			UInt32				m_indexCount;

			UInt32				m_width;
			UInt32				m_height;

			UInt32				m_resWidth;
			UInt32				m_resHeight;

			float*				m_pHeightData;
			float*				m_pFinalHeightData;

			StaticBuffer< TIKI_VERTEX_BUFFER >*	m_pVertexBuffer;
			StaticBuffer< TIKI_INDEX_BUFFER >*	m_pIndexBuffer;

			ID3D11Texture2D*			m_pHeightD3dTexture;
			Texture*					m_pHeightTexture;

			bool useCloddy;

			int size;
			int scale;
			float elevation;
			string fileName;

		};
	}
}