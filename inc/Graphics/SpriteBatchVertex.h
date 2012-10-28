#pragma once

#include "Core/TypeInc.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Vertices
	{
		// Implemented in GraphicsVertexFormats.cpp
		struct SpriteBatchVertex
		{
			Single Position[3];
			Single UV[3];
			
			bool operator==(const SpriteBatchVertex& rhs);

			static InputElement Declaration[2];
			static UInt32 DeclarationCount;

		};
	}
}