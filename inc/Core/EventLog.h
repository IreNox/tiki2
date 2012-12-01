#pragma once

#include "Core/Event.h"
#include "Core/TypeInc.h"

namespace TikiEngine
{
	class HelperLog;

	struct MessageReceivedArgs
	{
		cstring Message;
		MessageReceivedArgs(cstring message) : Message(message) {}
	};

	typedef Event<const HelperLog, MessageReceivedArgs> MessageReceivedEvent;
	typedef EventHandler<const HelperLog, MessageReceivedArgs> MessageReceivedEventHandler;
}