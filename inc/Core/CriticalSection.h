#pragma once

#include <Windows.h>

namespace TikiEngine
{
	class CriticalSection
	{
	public:

		CriticalSection()
		{
			InitializeCriticalSection(&cs);
		}

		~CriticalSection()
		{
			DeleteCriticalSection(&cs);
		}

		void Lock()
		{
			EnterCriticalSection(&cs);
		}

		void Unlock()
		{
			LeaveCriticalSection(&cs);
		}

	private:

		CRITICAL_SECTION cs;

	};
}