#pragma once

#include "Core/TypeDef.h"

class Object
{
public:

	Object();
	virtual ~Object();

	UInt32 AddRef();
	UInt32 Release();

private:

	UInt32 refCount;
};