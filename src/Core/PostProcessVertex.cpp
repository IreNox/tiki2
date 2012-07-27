
#include "Core/PostProcessVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		InputElement PostProcessVertex::Declaration[2] = {
			InputElement(InputElementType::Position, 0, InputElementFormat::Float, 3),
			InputElement(InputElementType::TexCoord, 0, InputElementFormat::Float, 2)
		};
	}
}