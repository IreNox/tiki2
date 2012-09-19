
#include "Graphics/TerrainRenderer.h"

namespace TikiEngine
{
	namespace Components
	{
		TerrainRenderer::TerrainRenderer(Engine* engine, GameObject* gameObject)
			: Component(engine, gameObject, CT_Renderer)
		{
		}

		TerrainRenderer::~TerrainRenderer()
		{
		}

		void TerrainRenderer::Draw(const DrawArgs& args)
		{
		}

		void TerrainRenderer::Update(const UpdateArgs& args)
		{

		}

		bool TerrainRenderer::GetReady()
		{
			return true;
		}
	}
}