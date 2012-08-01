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

string StringWtoA(wstring str)
{
	size_t size = str.length() + 1;
	size_t sizeOut;

	const char* cstr = new char[size];
		
	//wcstombs_s(&sizeOut, cstr, size, str.c_str(), size);

	string astr = cstr;
	delete(cstr);

	return astr;
}