#pragma once

#include "Core/TypeInc.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Vertices
	{
		struct PostProcessVertex
		{
			Single Position[3];
			Single UV[2];

			static InputElement Declaration[2];
		};
	}
}