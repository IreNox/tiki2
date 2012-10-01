#pragma once

#include "Core/TypeInc.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Vertices
	{
		struct DefaultVertex
		{
			Single Position[3];
			Single UV[2];

			Single Normal[3];
			Single Binormal[3];
			Single Tangent[3];

			static UInt32 DeclarationCount;
			static InputElement Declaration[5];
		};
	}
}