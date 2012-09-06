#pragma once

#include "Core/TypeInc.h"

template <class T>
inline void SafeAddRef(T** ptr)
{
	if (*ptr)
	{
		(*ptr)->AddRef();
	}
}

template <class T>
inline void SafeAddRef(T* src, T** dst)
{
	if (src)
	{
		src->AddRef();
		(*dst) = src;
	}
	else
	{
		(*dst) = 0;
	}
}

template <class T>
inline void SafeDelete(T** ptr)
{
	if (*ptr)
	{
		delete(*ptr);
		(*ptr) = 0;
	}
}

template <class T>
inline void SafeRelease(T** ptr)
{
	if (*ptr)
	{
		(*ptr)->Release();
		(*ptr) = 0;
	}
}

string StringWtoA(wstring str);
wstring StringAtoW(string str);