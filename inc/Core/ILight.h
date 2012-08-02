#pragma once

#include "Core/Component.h"
#include "Core/Color.h"

namespace TikiEngine
{
	namespace Components
	{
		enum LightType
		{
			LT_Point,
			LT_Directional,
			LT_Spot
		};

		class ILight : public Component
		{
		public:

			ILight(Engine* engine);
			virtual ~ILight();

			virtual Color GetColor() const = 0;
			virtual void SetColor(const Color& color) = 0;
			
			virtual LightType GetType() const = 0;
			virtual void SetType(LightType type) = 0;
		};
	}
}

