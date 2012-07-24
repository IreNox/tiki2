#pragma once

#include "Core/GameTime.h"
#include "Core/InputState.h"

namespace TikiEngine
{
	struct UpdateArgs
	{
		GameTime Time;
		InputState Input;

		UpdateArgs(GameTime time)
			: Time(time), Input()
		{	
		}

		~UpdateArgs()
		{
		}
	};
}

