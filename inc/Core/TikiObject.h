#pragma once

#include "Core/TypeDef.h"

class TikiObject
{
public:

	TikiObject();
	virtual ~TikiObject();

	UInt32 AddRef();
	UInt32 Release();

private:

	UInt32 refCount;
};