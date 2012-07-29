
#include "Core/PostProcessVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		InputElement PostProcessVertex::Declaration[2] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 2)
		};
	}
}