#pragma once

#include <set>
#include "Game/Telegram.h"
#include "Core/GameTime.h"

#define Dispatcher MessageDispatcher::Instance()

namespace TikiEngine
{
	namespace AI
	{
		class BaseGameEntity;


		const double SEND_MSG_IMMEDIATELY = 0.0;
		const int NO_ADDITIONAL_INFO   = 0;
		const int SENDER_ID_IRRELEVANT = -1;

		class MessageDispatcher
		{
		public:
			static MessageDispatcher* Instance();

			// send a message to another bot. The Receiving bot is referenced by ID.
			void DispatchMsg(const GameTime& time, double delay, int sender, int receiver, int msg, void* extraInfo);
			// send out any delayed messages. This method is called each time through the main game loop.
			void DispatchDelayedMessages();

		private:
			// this method is utilized by DispatchMsg or DispatchDelayedMessages.
			// This method calls the message handling member function of the receiving
			// entity, pReceiver, with the newly created telegram
			void Discharge(BaseGameEntity* receiver, const Telegram& msg);

			// a std::set is used as the container for the delayed messages
			// because of the benefit of automatic sorting and avoidance
			// of duplicates. Messages are sorted by their dispatch time.
			std::set<Telegram> priorityQ;

		};


	}
}