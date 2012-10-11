#pragma once

#include "Core/TypeInc.h"

class HelperLog
{
public:

	static void Write(string text);
	static void WriteError(string message, void* exception);

};