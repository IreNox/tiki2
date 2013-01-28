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

			EngineDescription(const EngineDescription& desc)
				: hInst(desc.hInst), Input(desc.Input), Sound(desc.Sound), Window(desc.Window), Graphics(desc.Graphics)
			{
				this->IgnoreModules = desc.IgnoreModules;
			}

			inline void operator=(const EngineDescription& rhs)
			{
				this->hInst = rhs.hInst;

				this->Input = rhs.Input;
				this->Sound = rhs.Sound;
				this->Window = rhs.Window;
				this->Graphics = rhs.Graphics;

				this->IgnoreModules = rhs.IgnoreModules;
			}
		};
	}
}