
#include "Core/HelperLog.h"
#include <Windows.h>

#include <sstream>
using namespace std;

//#define _CRT_SECURE_NO_WARNINGS

void HelperLog::Write(string text)
{
	FILE* h;
	fopen_s(&h, "engine.log", "a");

	fwrite(
		text.c_str(),
		1,
		text.size(),
		h
	);

	fclose(h);
}

void HelperLog::WriteError(string message, void* exception)
{
	ostringstream s;
	s << "Error: " << message << ". Exception: " << exception << endl;

	HelperLog::Write(s.str());

	throw s.str().c_str();
}