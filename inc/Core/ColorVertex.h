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

			static InputElement Declaration[2];
		};
	}
}