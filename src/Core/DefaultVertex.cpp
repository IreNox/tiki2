
#include "Core/Engine.h"
#include "Core/DefaultVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		InputElement DefaultVertex::Declaration[3] = {
			InputElement(InputSemanticType::IST_Position, 0, InputElementFormat::IEF_Float, 3),
			InputElement(InputSemanticType::IST_Normal,   0, InputElementFormat::IEF_Float, 3),
			InputElement(InputSemanticType::IST_TexCoord, 0, InputElementFormat::IEF_Float, 2)
		};
	}
}
