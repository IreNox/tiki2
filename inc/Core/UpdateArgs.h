#pragma once

#include "Core/GameTime.h"
#include "Core/InputState.h"

namespace TikiEngine
{
	// Implementation in AllArgs.cpp
	struct UpdateArgs
	{
	public:
		static const UpdateArgs Empty;

		GameTime Time;
		InputState Input;

		UpdateArgs()
			: Time(), Input()
		{
		}

		UpdateArgs(GameTime time)
			: Time(time), Input()
		{	
		}

		~UpdateArgs()
		{
		}

	};
}

