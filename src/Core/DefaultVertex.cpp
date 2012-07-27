
#include "Core/Engine.h"
#include "Core/DefaultVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		InputElement DefaultVertex::Declaration[3] = {
			InputElement(InputElementType::Position, 0, InputElementFormat::Float, 3),
			InputElement(InputElementType::Normal,   0, InputElementFormat::Float, 3),
			InputElement(InputElementType::TexCoord, 0, InputElementFormat::Float, 2)
		};
	}
}
