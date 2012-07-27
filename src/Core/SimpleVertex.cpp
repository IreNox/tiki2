
#include "Core/SimpleVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		InputElement SimpleVertex::Declaration[1] = {
			InputElement(InputSemanticType::IST_Position, 0, InputElementFormat::IEF_Float, 3)
		};
	}
}

