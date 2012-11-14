#pragma once

#include "Core/EventLog.h"

namespace TikiEngine
{
	class HelperLog
	{
	public:

		static MessageReceivedEvent MessageReceived;

		static void Write(string text);
		static void WriteError(string message, void* exception);

	};
}
