
#include "Core/TypeGlobals.h"
#include <stdlib.h>

float Random(float min, float max)
{
	return (((float)rand() / RAND_MAX) * (max - min)) + min;
}

string StringWtoA(wstring str)
{
	size_t size = str.Length() + 1;
	size_t sizeOut;

	char* cstr = TIKI_NEW char[size];

	wcstombs_s(&sizeOut, cstr, size, str.CStr(), size);

	string astr = cstr;
	delete(cstr);

	return astr;
}

wstring StringAtoW(string str)
{
	size_t size = str.Length() + 1;
	size_t sizeOut;

	wchar_t* cstr = TIKI_NEW wchar_t[size];

	mbstowcs_s(&sizeOut, cstr, size, str.CStr(), size);

	wstring astr = cstr;
	delete(cstr);

	return astr;
}