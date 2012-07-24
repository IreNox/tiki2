#pragma once

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

	unsigned int AddRef()
	{
		return ++refCount;
	}

	unsigned int Release()
	{
		refCount--;

		if (refCount < 1)
		{
			GC::Destroy(this);
		}

		return refCount;
	}

private:

	unsigned int refCount;
};