#pragma once

#include "Core/TypeDef.h"
#include "Core/GameTime.h"
#include "Core/UpdateArgs.h"

#include "Core/BufferedVariable.h"

namespace TikiEngine
{
	struct BufferState
	{
		bool Running;

		union
		{
			struct
			{
				Byte DrawIndex;
				Byte UpdateIndex;
			};
			Byte Indices[2];
		};

		GameTime CurrentTime;
#ifdef TIKI_MULTITHREADING
		BVar<UpdateArgs> UpdateState;
#else
		UpdateArgs UpdateState;
#endif


		BufferState()
			: Running(true), CurrentTime(), UpdateState()
		{
			this->DrawIndex = 0;

#ifdef TIKI_MULTITHREADING
			this->UpdateIndex = 1;
#else
			this->UpdateIndex = 0;
#endif
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