#pragma once

#include "Core/TypeDef.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Vertices
	{
		// Implemented in GraphicsVertexFormats.cpp
		struct ParticleVertex 
		{
			Single Position[3];
			Single Color[4];

			/*! @brief 1 - SizeX, 2 - SizeY, 3 - Rotation */
			Single SizeRotation[3];

			static InputElement Declaration[3];
			static UInt32 DeclarationCount;

		};
	}
}