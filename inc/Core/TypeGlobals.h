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

string StringWtoA(wstring str);
wstring StringAtoW(string str);