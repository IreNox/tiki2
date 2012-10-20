#pragma once

#include "Core/Matrix.h"

namespace TikiEngine
{
	// Constant Buffer Matrices
	struct CBMatrices 
	{
		Matrix ViewMatrix;
		Matrix ProjectionMatrix;
	};
}