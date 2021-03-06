#pragma once

#include "Core/EventLog.h"

namespace TikiEngine
{
	class HelperLog
	{
	public:
		
		ConsoleCommandEvent ConsoleCommand;
		MessageReceivedEvent MessageReceived;

		HelperLog();
		~HelperLog();

		void Write(string text, bool output = true) const;
		void WriteError(string message, void* exception) const;

	};
}
