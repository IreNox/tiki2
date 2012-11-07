
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
			return (this->Position[0] == rhs.Position[0]) &&
				   (this->Position[1] == rhs.Position[1]) &&
  				   (this->Position[2] == rhs.Position[2]) &&
				   (this->UV[0] == rhs.UV[0]) &&
				   (this->UV[1] == rhs.UV[1]) &&
				   (this->UV[2] == rhs.UV[2]) &&
				   (this->Color[0] == rhs.Color[0]) &&
				   (this->Color[1] == rhs.Color[1]) &&
				   (this->Color[2] == rhs.Color[2]) &&
				   (this->Color[3] == rhs.Color[3]);
		}

		InputElement SpriteBatchVertex::Declaration[3] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 3),
			InputElement(IST_Color,    0, IEF_Float, 4)
		};

		UInt32 SpriteBatchVertex::DeclarationCount = 3;
	}
}

