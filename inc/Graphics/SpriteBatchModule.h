#pragma once

#include "Core/ISpriteBatch.h"

#include "Graphics/Shader.h"
#include "Graphics/VertexBuffer.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Graphics;

		class SpriteBatchModule : public ISpriteBatch
		{
		public:

			SpriteBatchModule(Engine* engine);
			~SpriteBatchModule();

			void Begin();

			void Draw(ITexture* texture, const Vector2& position);
			void Draw(ITexture* texture, const Rectangle& destinationRectangle);

			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth);
			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth);

			void End();

			void Dispose();

		private:

			Shader* shader;
			VertexBuffer* vertexBuffer;

			void drawInternal(ITexture* texture, const Vector2& topLeft, const Vector2& rightBottom, float rotation);

		};
	}
}