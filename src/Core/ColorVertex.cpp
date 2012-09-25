
#include "Core/Engine.h"
#include "Core/ColorVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		bool ColorVertex::operator==(const ColorVertex& rhs)
		{
			return (this->Position[0] == rhs.Position[0]) &&
	  			   (this->Position[1] == rhs.Position[1]) &&
				   (this->Position[2] == rhs.Position[2]) &&
				   (this->Color[0] == rhs.Color[0]) &&
				   (this->Color[1] == rhs.Color[1]) &&
				   (this->Color[2] == rhs.Color[2]) &&
				   (this->Color[3] == rhs.Color[3]);
		}

		UInt32 ColorVertex::DeclarationCount = 2;

		InputElement ColorVertex::Declaration[2] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_Color,    0, IEF_Float, 4)
		};
	}
}
