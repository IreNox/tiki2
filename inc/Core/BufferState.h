#pragma once

#include "Core/TypeDef.h"
#include "Core/GameTime.h"

namespace TikiEngine
{
	struct UpdateArgs;

	struct BufferState
	{
		bool Running;

		Byte DrawIndex;
		Byte UpdateIndex;

		GameTime CurrentTime;
		UpdateArgs* UpdateState[2];

		BufferState()
			: Running(true), CurrentTime()
		{
			this->DrawIndex = 0;

#ifdef TIKI_MULTITHREADING
			this->UpdateIndex = 1;
#else
			this->UpdateIndex = 0;
#endif

			this->UpdateState[0] = 0;
			this->UpdateState[1] = 0;
		}

		void Swap(GameTime time)
		{
#ifdef TIKI_MULTITHREADING
			if (this->DrawIndex == 1)
			{
				this->DrawIndex = 0;
				this->UpdateIndex = 1;
			}
			else
			{
				this->DrawIndex = 1;
				this->UpdateIndex = 0;
			}
#endif

			this->CurrentTime = time;
		}
	};
}