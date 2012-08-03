
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
			UInt32 Count;
			LightData Data[32];
			LightProperties Props;
		};
	}
}