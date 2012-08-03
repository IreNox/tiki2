#pragma once

#include "Core/TypeInc.h"

namespace TikiEngine
{
	namespace Graphics
	{
		struct LightProperties
		{
			float DiffuseIntensity;
			float AmbientIntensity;
			float EmissiveIntensity;

			Color AmbientColor;
			Color EmissiveColor;

			LightProperties()
				: DiffuseIntensity(1.0f), AmbientIntensity(0.1f), EmissiveIntensity(0.2f),
				  AmbientColor(0.3f, 0.2f, 0.0f, 1.0f), EmissiveColor(1.0f, 1.0f, 1.0f, 1.0f)
			{
			}

			~LightProperties()
			{
			}
		};
	}
}