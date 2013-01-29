
#include "Core/HelperLog.h"
#include <Windows.h>

#include <sstream>
using namespace std;

namespace TikiEngine
{
	HelperLog::HelperLog()
		: MessageReceived()
	{
		FILE* h;
		fopen_s(&h, "engine.log", "w");
		fclose(h);
	}

	HelperLog::~HelperLog()
	{
	}

	void HelperLog::Write(string text, bool output) const
	{
		if (output)
		{
			MessageReceived.RaiseEvent(this, MessageReceivedArgs(text.CStr()));
		}

		text += "\n";

		FILE* h;
		fopen_s(&h, "engine.log", "a");
		
		if (h != 0)
		{
			fwrite(
				text.CStr(),
				1,
				text.Length(),
				h
				);

			fclose(h);
		}
	}

	void HelperLog::WriteError(string message, void* exception) const
	{
		string error = "Error: " + message + ". Exception: " + StringConvert::ToString((Int64)exception) + "\n";

		HelperLog::Write(error);

		throw error;
	}
}

