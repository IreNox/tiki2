#pragma once

#include "Core/IResource.h"

#include "Core/Vector2.h"
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

			virtual float DrawChar(wchar_t c, const Vector2& pos) = 0;

			virtual UInt32 GetHeight() = 0;
			virtual ITexture* GetTexture() = 0;
		};
	}
}