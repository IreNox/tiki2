#pragma once

#include "Core/TypeDef.h"
#include <Windows.h>

namespace TikiEngine
{
	class TikiPerformanceCounter
	{
	public:

		TikiPerformanceCounter() {}
		~TikiPerformanceCounter() {}

		void Start()
		{
			QueryPerformanceFrequency(&freq);
			QueryPerformanceCounter(&last);
		}

		double Stop()
		{
			QueryPerformanceCounter(&now);
			return (double)(now.QuadPart - last.QuadPart) / (double)freq.QuadPart;
		}

	private:

		LARGE_INTEGER freq;
		LARGE_INTEGER last;
		LARGE_INTEGER now;

	};
}