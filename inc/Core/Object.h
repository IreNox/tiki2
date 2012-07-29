#pragma once

#include "Core/TypeDef.h"
#include "Core/GarbageCollector.h"

class Object
{
public:

	Object()
		: refCount(1)
	{	
	}

	~Object()
	{
		//if (refCount > 0)
		//{
		//	throw "Used object destroyed.";
		//}
	}

	UInt32 AddRef()
	{
		return ++refCount;
	}

	UInt32 Release()
	{
		refCount--;

		if (refCount == 0)
		{
			GC::Destroy(this);
		}

		return refCount;
	}

private:

	UInt32 refCount;
};