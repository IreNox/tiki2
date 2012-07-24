#pragma once

#include "Core/InputDescription.h"
#include <Core/WindowDescription.h>
#include <Core/GraphicsDescription.h>

namespace TikiEngine
{
	namespace Description
	{
		struct EngineDescription
		{
			HINSTANCE hInst;

			InputDescription Input;
			WindowDescription Window;
			GaphicsDescription Graphics;

			EngineDescription()
				: hInst(0), Input(), Window(), Graphics()
			{
			}
		};
	}
}