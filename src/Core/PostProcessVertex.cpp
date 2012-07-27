
#include "Core/PostProcessVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		InputElement PostProcessVertex::Declaration[2] = {
			InputElement(InputSemanticType::IST_Position, 0, InputElementFormat::IEF_Float, 3),
			InputElement(InputSemanticType::IST_TexCoord, 0, InputElementFormat::IEF_Float, 2)
		};
	}
}