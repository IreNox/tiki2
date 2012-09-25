#pragma once

#include "Core/TypeInc.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Vertices
	{
		struct ColorVertex
		{
			Single Position[3];
			Single Color[4];

			bool operator==(const ColorVertex& rhs);

			static UInt32 DeclarationCount;
			static InputElement Declaration[2];
		};
	}
}