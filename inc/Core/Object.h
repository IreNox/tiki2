#pragma once

#include "Core/TypeDef.h"

class Object
{
public:

	Object()
		: refCount(1)
	{	
	}

	virtual ~Object()
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
			delete this;
		}

		return refCount;
	}

private:

	UInt32 refCount;
};