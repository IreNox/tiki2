
#include "Core/HelperThreading.h"

#include <Windows.h>

namespace TikiEngine
{
#ifdef TIKI_MULTITHREADING
	UInt32 HelperThreading::threadId[2] = { 0, 0 };
#else
	UInt32 HelperThreading::threadId[1] = { 0 };
#endif	

	void HelperThreading::InitThread(UInt32 id)
	{
		threadId[id] = GetCurrentThreadId();
	}

	void HelperThreading::Swap()
	{
#ifdef TIKI_MULTITHREADING
		UInt32 id0 = threadId[0];

		threadId[0] = threadId[1];
		threadId[1] = id0;
#endif
	}

	UInt32 HelperThreading::GIndex()
	{
		return GetCurrentThreadId(); // (GetCurrentThreadId() == threadId[0] ? 0 : 1);
	}
}