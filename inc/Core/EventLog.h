#pragma once

#include "Core/Event.h"
#include "Core/TypeInc.h"

namespace TikiEngine
{
	struct MessageReceivedArgs
	{
		cstring Message;

		MessageReceivedArgs(cstring message) : Message(message) {}
	};

	typedef Event<void, MessageReceivedArgs> MessageReceivedEvent;
	typedef EventHandler<void, MessageReceivedArgs> MessageReceivedEventHandler;
}