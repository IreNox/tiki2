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

			Single Color[4];
			
			bool operator==(const SpriteBatchVertex& rhs);

			static InputElement Declaration[3];
			static UInt32 DeclarationCount;

		};
	}
}