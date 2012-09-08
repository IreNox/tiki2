#pragma once

#include "Core/TypeInc.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Vertices
	{
		struct SpriteBatchVertex
		{
			Single Position[3];
			Single UV[3];
			
			bool operator==(const SpriteBatchVertex& rhs);

			static InputElement Declaration[2];
		};
	}
}