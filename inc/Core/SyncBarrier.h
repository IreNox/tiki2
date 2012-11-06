#pragma once

#include "Core/TikiObject.h"
#include <Windows.h>

namespace TikiEngine
{
	class SyncBarrier : public TikiObject
	{
	public:

		SyncBarrier(UInt32 threadCount);
		~SyncBarrier();

		void Enter();

	private:

		UInt32 threadCount;

	};
}