
#include "Core/TypeGlobals.h"
#include "Core/LightProperties.h"

namespace TikiEngine
{
	namespace Graphics
	{
		struct LightData
		{
			Vector3 Position;
			Vector3 Direction;
			Vector3 Color;
			float Range;
		};

		struct Lights
		{
			float Count;
			LightProperties Props;

			LightData Data[32];

			Lights()
				: Count(0), Props()
			{
			}
		};
	}
}