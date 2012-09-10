#pragma once

#include "Core/EngineObject.h"

#include "Core/Vector2.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Resources;

		class Font : public EngineObject
		{
		public:

			Font(Engine* engine);
			~Font();

			void Create(wcstring fontName);

			float DrawChar(wchar_t c, const Vector2& pos);

			float GetHeight();
			ITexture* GetTexture();

		private:

			float maxHeight;

			ITexture* texture;

		};
	}
}