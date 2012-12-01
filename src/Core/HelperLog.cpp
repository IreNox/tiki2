
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
			MessageReceived.RaiseEvent(this, MessageReceivedArgs(text.c_str()));
		}

		FILE* h;
		fopen_s(&h, "engine.log", "a");
		
		text += "\n";

		fwrite(
			text.c_str(),
			1,
			text.size(),
			h
		);

		fclose(h);
	}

	void HelperLog::WriteError(string message, void* exception) const
	{
		ostringstream s;
		s << "Error: " << message << ". Exception: " << exception << endl;

		HelperLog::Write(s.str());

		throw s.str().c_str();
	}
}

