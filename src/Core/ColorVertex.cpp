
#include "Core/Engine.h"
#include "Core/ColorVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		InputElement ColorVertex::Declaration[2] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_Color,    0, IEF_Float, 4)
		};
	}
}
