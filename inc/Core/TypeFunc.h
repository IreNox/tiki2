#pragma once

#include "Core/TypeInc.h"

template <class T>
void SafeRelease(T** ptr)
{
	if (*ptr)
	{
		(*ptr)->Release();
		(*ptr) = 0;
	}
}