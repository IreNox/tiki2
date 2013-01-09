#pragma once

#include "Core/ISpriteBatch.h"

#include "Core/EventScreenSizeChanged.h"

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

		class SpriteBatchModule : public ISpriteBatch, public ScreenSizeChangedEventHandler
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
			void Draw(ITexture* texture,  const Rectangle& destinationRectangle, const Rectangle& sourceRectangle);

			void Draw(ITexture* texture,  const RectangleF& destinationRectangle, const Color& color);
			void Draw(ITexture* texture,  const RectangleF& destinationRectangle, const Color& color, float layerDepth);
			void Draw(ITexture* texture,  const RectangleF& destinationRectangle, const RectangleF& sourceRectangle, const Color& color);
			void Draw(ITexture* texture,  const RectangleF& destinationRectangle, const RectangleF& sourceRectangle, const Color& color, float layerDepth);

			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth);
			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth);
			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth, const Color& color);
			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth, const Color& color);
			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth, const Color& color, float value);
			
			void DrawString(IFont* font, wstring text, const Vector2& position, const Color& color, float layerDepth = 1.0f);

			void Handle(IGraphics* graphics, const ScreenSizeChangedArgs& args);

		private:

			struct Sprite
			{
				UInt32 BufferIndex;
				UInt32 TextureIndex;

				float Value;
				float LayerDepth;

				inline bool operator>(const Sprite& rhs) const { return LayerDepth > rhs.LayerDepth; }
				inline bool operator<(const Sprite& rhs) const { return LayerDepth < rhs.LayerDepth; }
				inline bool operator>=(const Sprite& rhs) const { return LayerDepth >= rhs.LayerDepth; }
				inline bool operator<=(const Sprite& rhs) const { return LayerDepth <= rhs.LayerDepth; }
				inline bool operator==(const Sprite& rhs) const { return LayerDepth == rhs.LayerDepth; }
				inline bool operator!=(const Sprite& rhs) const { return LayerDepth != rhs.LayerDepth; }
			};

			Shader* shader;
			VertexDeclaration* declaration;
			DynamicBuffer<SpriteBatchVertex, D3D11_BIND_VERTEX_BUFFER>* buffer;

			List<Sprite> spriteInfos;
			List<ITexture*> spriteTextures;
			List<SpriteBatchVertex> spriteVertices;
						
			Vector2 screenSize;
			Matrix projMatrix;

			Vector3 transformPoint(const Vector3& point);

			void drawInternal(ITexture* texture, const Vector3& tl, const Vector3& tr, const Vector3& bl, const Vector3& br, const Vector4& texCorrd, const Color& color, float value = 0);

		};
	}
}