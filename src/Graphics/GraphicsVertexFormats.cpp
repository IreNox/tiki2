
#include "Graphics/ParticleVertex.h"
#include "Graphics/SpriteBatchVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		InputElement ParticleVertex::Declaration[3] = {
			InputElement(IST_Position,	0, IEF_Float, 3),
			InputElement(IST_Color,		0, IEF_Float, 4),
			InputElement(IST_TexCoord,	0, IEF_Float, 3)
		};

		UInt32 ParticleVertex::DeclarationCount = 3;

		bool SpriteBatchVertex::operator==(const SpriteBatchVertex& rhs)
		{
			return (this->Position == rhs.Position) && (this->UV == rhs.UV);
		}

		InputElement SpriteBatchVertex::Declaration[2] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 3)
		};

		UInt32 SpriteBatchVertex::DeclarationCount = 2;
	}
}

