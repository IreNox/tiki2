#pragma once

#include "Core/GameTime.h"
#include "Core/InputState.h"

namespace TikiEngine
{
	// Implementation in AllArgs.cpp
	struct UpdateArgs
	{
		static const UpdateArgs Empty;

		GameTime Time;
		InputState Input;

		UpdateArgs(GameTime time)
			: Time(time), Input()
		{	
		}

		~UpdateArgs()
		{
		}

	private:

		UpdateArgs()
			: Time(), Input()
		{
		}

	};
}

