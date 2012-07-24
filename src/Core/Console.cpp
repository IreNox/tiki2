
#include <Windows.h>

#include "Core/Console.h"

//#define _CRT_SECURE_NO_WARNINGS

void Console::Write(string text)
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

void Console::WriteError(string message, HRESULT code)
{
	Console::Write("Error: " + message + ". Code:\n"); //HRESULT_CODE(code)

	throw message.c_str();
}