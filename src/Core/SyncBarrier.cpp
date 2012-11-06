
#include "Core/SyncBarrier.h"

namespace TikiEngine
{
	SyncBarrier::SyncBarrier(UInt32 threadCount)
		: threadCount(threadCount)
	{
		//InitializeSynchronizationBarrier();
	}

	SyncBarrier::~SyncBarrier()
	{

	}
}