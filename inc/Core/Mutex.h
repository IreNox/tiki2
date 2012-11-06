#pragma once

#include "Core/TikiObject.h"
#include <Windows.h>

namespace TikiEngine
{
	class Mutex : public TikiObject
	{
	public:

		Mutex();
		~Mutex();

		/*! @brief Block the current Thread while this Mutex is locked. */
		void Wait();

		/*! @brief Block the current Thread while all Mutexs are locked. */
		static void WaitForMultiple(Mutex* arr, UInt32 count, bool waitForAll = true);

		/*! @brief Unlock this Mutex. */
		void Unlock();

	private:

		HANDLE handle;

	};
}