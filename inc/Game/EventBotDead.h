#pragma once

#include "Core/Event.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiBot;

		struct BotDeadArgs
		{
			TikiBot* killedBot;

			BotDeadArgs(TikiBot* killed)
			{
				this->killedBot = killed;
			}
		};

		typedef Event<TikiBot, BotDeadArgs> BotDeadEvent;
		typedef EventHandler<TikiBot, BotDeadArgs> BotDeadEventHandler;

	}
}