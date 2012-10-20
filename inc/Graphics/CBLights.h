
#include "Core/TypeGlobals.h"
#include "Core/LightProperties.h"

#include "Graphics/LightData.h"

namespace TikiEngine
{
	namespace Graphics
	{
		// Constant Buffer Lights
		struct CBLights
		{
			float Count;
			LightProperties Props;

			LightData Data[32];

			CBLights()
				: Count(0), Props()
			{
			}
		};
	}
}