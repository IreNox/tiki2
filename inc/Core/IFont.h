#pragma once

#include "Core/IResource.h"

#include "Core/TypeInc.h"
#include "Core/ITexture.h"

namespace TikiEngine
{
	namespace Resources
	{
		class IFont : public IResource
		{
		public:

			IFont(Engine* engine) : IResource(engine) {}
			~IFont() {}

			virtual void Create(wcstring fontName, float fontSize) = 0;

			virtual float DrawChar(wchar_t c, const Vector2& pos, const Color& color) = 0;

			virtual ITexture* GetTexture() = 0;

			virtual float GetHeight() = 0;
			virtual bool ContainsChar(wchar_t cChar) = 0;
			virtual Vector2 MeasureString(wstring text) = 0;

		};
	}
}