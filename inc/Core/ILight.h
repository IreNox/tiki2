#pragma once

#include "Core/IElement.h"
#include "Core/Color.h"

namespace TikiEngine
{
	namespace Elements
	{
		class ILight : public IElement
		{
		public:

			ILight(Engine* engine);
			virtual ~ILight();

			virtual Color GetColor() const = 0;
			virtual void SetColor(const Color& color) = 0;
		};
	}
}

