#pragma once

#include "Core/TypeInc.h"

class Console
{
public:
	static void Write(string text);
	static void WriteError(string message, Int32 code);
};