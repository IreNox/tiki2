
#include "Core/Mutex.h"

namespace TikiEngine
{
	Mutex::Mutex()
	{
		handle = CreateMutex(0, true, 0);
	}

	Mutex::~Mutex()
	{
		ReleaseMutex(handle);
	}

	void Mutex::Wait()
	{
		WaitForSingleObject(handle, INFINITE);
	}

	void Mutex::WaitForMultiple(Mutex* arr, UInt32 count, bool wfa)
	{
		HANDLE* handles = (HANDLE*)arr;

		//UInt32 i = 0;
		//while (i < count) { handles[i++] = arr[i]->handle; }

		WaitForMultipleObjects(count, handles, wfa, INFINITE);
		
		//delete[](handles);
	}
	
	void Mutex::Unlock()
	{
		ReleaseMutex(handle);
		//handle = CreateMutex(0, true, 0);
	}
}