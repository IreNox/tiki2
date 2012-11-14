
#include "Core/HelperLog.h"
#include <Windows.h>

#include <sstream>
using namespace std;

namespace TikiEngine
{
	MessageReceivedEvent HelperLog::MessageReceived = MessageReceivedEvent();

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

		MessageReceived.RaiseEvent(
			0,
			MessageReceivedArgs(text.c_str())
		);
	}

	void HelperLog::WriteError(string message, void* exception)
	{
		ostringstream s;
		s << "Error: " << message << ". Exception: " << exception << endl;

		HelperLog::Write(s.str());

		throw s.str().c_str();
	}
}

