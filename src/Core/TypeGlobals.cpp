
#include "Core/TypeGlobals.h"

float Random(float min, float max)
{
	return (((float)rand() / RAND_MAX) * (max - min)) + min;
}

string StringWtoA(wstring str)
{
	size_t size = str.length() + 1;
	size_t sizeOut;

	char* cstr = new char[size];

	wcstombs_s(&sizeOut, cstr, size, str.c_str(), size);

	string astr = cstr;
	delete(cstr);

	return astr;
}

wstring StringAtoW(string str)
{
	size_t size = str.length() + 1;
	size_t sizeOut;

	wchar_t* cstr = new wchar_t[size];

	mbstowcs_s(&sizeOut, cstr, size, str.c_str(), size);

	wstring astr = cstr;
	delete(cstr);

	return astr;
}