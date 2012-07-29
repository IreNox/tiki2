
#include "Core/Engine.h"
#include "Core/DefaultVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		InputElement DefaultVertex::Declaration[3] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_Normal,   0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 2)
		};
	}
}
