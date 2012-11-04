#pragma once

#include "Core/TypeDef.h"
#include "Core/GameTime.h"

namespace TikiEngine
{
	struct BufferState
	{
		Byte DrawIndex;
		Byte UpdateIndex;

		GameTime CurrentTime;

		BufferState()
			: DrawIndex(0), UpdateIndex(1), CurrentTime()
		{
		}

		void Swap(GameTime time)
		{
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

			this->CurrentTime = time;
		}
	};
}