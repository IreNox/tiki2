#pragma once

#include "Core/TypeInc.h"

class TikiObject
{
public:

#if _DEBUG
	static List<void*> WatchPointer;
#endif

	TikiObject();
	virtual ~TikiObject();

	UInt32 AddRef();
	UInt32 Release();

private:

	UInt32 refCount;
};