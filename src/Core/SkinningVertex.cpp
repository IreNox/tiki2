
#include "Core/Engine.h"
#include "Core/SkinningVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		UInt32 SkinningVertex::DeclarationCount = 5;

		InputElement SkinningVertex::Declaration[5] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 2),
			InputElement(IST_Normal,   0, IEF_Float, 3),
			InputElement(IST_SkinningWeight,0,IEF_Float,4),
			InputElement(IST_SkinningIndices,0,IEF_Float,4)
		};
	}
}
