#pragma once

#include "Core/TypeInc.h"

class TikiObject
{
public:

	TikiObject();
	virtual ~TikiObject();

	Int32 AddRef();
	Int32 Release();

private:

	Int32 refCount;
};