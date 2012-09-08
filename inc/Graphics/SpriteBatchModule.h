#pragma once

#include "Core/ISpriteBatch.h"

#include "Graphics/Shader.h"
#include "Graphics/DynamicBuffer.h"
#include "Graphics/VertexDeclaration.h"
#include "Graphics/SpriteBatchVertex.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Graphics;
		using namespace TikiEngine::Vertices;

		class SpriteBatchModule : public ISpriteBatch
		{
		public:

			SpriteBatchModule(Engine* engine);
			~SpriteBatchModule();

			bool Initialize(EngineDescription& desc);
			void Dispose();

			void Begin();
			void End();

			void Draw(ITexture* texture, const Vector2& position);
			void Draw(ITexture* texture, const Rectangle& destinationRectangle);

			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth);
			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth);
			
		private:

			Shader* shader;
			VertexDeclaration* declaration;
			DynamicBuffer<SpriteBatchVertex, D3D11_BIND_VERTEX_BUFFER>* buffer;

			List<ITexture*> textures;
			List<SpriteBatchVertex> vertices;

			void drawInternal(ITexture* texture, const Vector2& position, const Vector2& size, const Vector2& origin, float rotation);

		};
	}
}