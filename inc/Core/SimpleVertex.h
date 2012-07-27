#pragma once

#include "Core/TypeInc.h"
#include "Core/InputElement.h"
			
namespace TikiEngine
{
	namespace Vertices
	{
		struct SimpleVertex
		{
			Single Position[3];

			static InputElement Declaration[1];
		};
	}
}