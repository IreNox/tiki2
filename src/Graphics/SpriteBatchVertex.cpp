
#include "Graphics/SpriteBatchVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		bool SpriteBatchVertex::operator==(const SpriteBatchVertex& rhs)
		{
			return (this->Position == rhs.Position) && (this->UV == rhs.UV);
		}

		InputElement SpriteBatchVertex::Declaration[2] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 3)
		};
	}
}

