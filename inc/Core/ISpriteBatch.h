#pragma once

#include "Core/IModule.h"

#include "Core/Vector2.h"
#include "Core/Rectangle.h"
#include "Core/RectangleF.h"

#include "Core/IFont.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Resources;

		class ISpriteBatch : public IModule
		{
		public:

			ISpriteBatch(Engine* engine) : IModule(engine) {}
			~ISpriteBatch() {}

			virtual void Draw(ITexture* texture, const Vector2& position) = 0;
			virtual void Draw(ITexture* texture, const Rectangle& destinationRectangle) = 0;
			virtual void Draw(ITexture* texture, const Rectangle& destinationRectangle, const Rectangle& sourceRectangle) = 0;

			virtual void Draw(ITexture* texture, const RectangleF& destinationRectangle, const Color& color) = 0;
			virtual void Draw(ITexture* texture, const RectangleF& destinationRectangle, const Color& color, float layerDepth) = 0;
			virtual void Draw(ITexture* texture, const RectangleF& destinationRectangle, const RectangleF& sourceRectangle, const Color& color) = 0;
			virtual void Draw(ITexture* texture, const RectangleF& destinationRectangle, const RectangleF& sourceRectangle, const Color& color, float layerDepth) = 0;

			virtual void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth) = 0;
			virtual void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth) = 0;
			virtual void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, float scale, float layerDepth, const Color& color) = 0;
			virtual void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth, const Color& color) = 0;
			virtual void Draw(ITexture* texture, const Vector2& position, float rotation, const Vector2& origin, const Vector2& scale, float layerDepth, const Color& color, float value) = 0;

			virtual void DrawString(IFont* font, wstring text, const Vector2& position, const Color& color, float layerDepth = 1.0f) = 0;

		};
	}
}