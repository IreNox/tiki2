#pragma once

#include "Core/Matrix.h"

namespace TikiEngine
{
	namespace Graphics
	{
		// Constant Buffer Object Data
		struct CBObjectData 
		{
			/*! @brief World Matrix */
			Matrix WorldM;

			/*! @brief World Inverse Transposed Matrix */
			Matrix WorldMIT;

			Boolean UseDiffuse;
			Boolean UseLightMap;
			Boolean UseNormalMap;
			Boolean UseSpecularMap;
			
		};
	}
}