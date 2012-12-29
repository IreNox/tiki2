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
			void Draw(ITexture* texture,  const RectangleF& destinationRectangle, const RectangleF& sourceRectangle, const Color& color);

			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth);
			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth);
			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth, const Color& color);
			void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth, const Color& color);
			
			void DrawString(IFont* font, wstring text, const Vector2& position, const Color& color);

			void Handle(IGraphics* graphics, const ScreenSizeChangedArgs& args);

		private:

			//struct LocalWorldMatrices
			//{
			//	Matrix LocalM;
			//	Matrix WorldM;
			//};

			Shader* shader;
			VertexDeclaration* declaration;
			DynamicBuffer<SpriteBatchVertex, D3D11_BIND_VERTEX_BUFFER>* buffer;
						
			Dictionary<ITexture*, List<SpriteBatchVertex>> sprites;
			//Dictionary<UInt32, LocalWorldMatrices> matrices;

			Vector2 pixelSize;
			Vector2 screenSize;

			//Matrix viewMatrix;
			//Matrix projMatrix;

			Vector3 transformPoint(Vector3 point);

			void drawInternal(ITexture* texture, const Vector3& tl, const Vector3& tr, const Vector3& bl, const Vector3& br, const Vector4& texCorrd, const Color& color);

		};
	}
}