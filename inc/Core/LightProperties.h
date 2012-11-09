#pragma once

#include "Core/TypeInc.h"

namespace TikiEngine
{
	namespace Graphics
	{
		struct LightProperties
		{
			float specularity;
			float UnusedTemp[2];

			float DiffuseIntensity;
			float AmbientIntensity;
			float EmissiveIntensity;
			float SpecularIntensity;

			Color AmbientColor;
			Color EmissiveColor;
			//Color SpecularColor;


			LightProperties()
				: DiffuseIntensity(1.0f), AmbientIntensity(0.1f), EmissiveIntensity(0.2f), SpecularIntensity(1.0f),
				  AmbientColor(0.3f, 0.2f, 0.0f, 1.0f), EmissiveColor(1.0f, 1.0f, 1.0f, 1.0f), //SpecularColor(1.0f, 1.0f, 1.0f, 1.0f),
				  specularity(100)
			{
			}

			~LightProperties()
			{
			}
		};
	}
}