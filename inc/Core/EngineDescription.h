#pragma once

#define NOMINMAX
#include <Windows.h>

#include "Core/InputDescription.h"
#include "Core/SoundDescription.h"
#include "Core/WindowDescription.h"
#include "Core/GraphicsDescription.h"

namespace TikiEngine
{
	namespace Description
	{
		struct EngineDescription
		{
			HINSTANCE hInst;

			InputDescription Input;
			SoundDescription Sound;
			WindowDescription Window;
			GaphicsDescription Graphics;

			List<wstring> IgnoreModules;

			EngineDescription()
				: hInst(0), Input(), Sound(), Window(), Graphics()
			{
			}
		};
	}
}