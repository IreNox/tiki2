
#include <sstream>
#include "Game/MessageDispatcher.h"
#include "Game/EntityManager.h"

namespace TikiEngine
{
	namespace AI
	{
		MessageDispatcher::MessageDispatcher(EntityManager* mgr)
		{
			this->entityMgr = mgr;
		}


		void MessageDispatcher::Discharge(BaseGameEntity* pReceiver, const Telegram& telegram)
		{
		    if (!pReceiver->HandleMessage(telegram))
		    {
				#ifdef _DEBUG
				OutputDebugString(L"Telegram could not be handled");
				#endif
			}
		}

		void MessageDispatcher::DispatchMsg(const GameTime& time, double delay, int sender, int receiver, int msg, void* extraInfo)
		{
			BaseGameEntity* receiverEnt = entityMgr->GetEntityFromID(receiver);

			if (receiverEnt == 0)
			{
				std::wostringstream s;
				s << "\nTelegram dispatched at time: " << time.TotalTime	// Get current frame
				  << " by " << sender << " for " << receiver  << ". Msg is " << msg << "";
				OutputDebugString(s.str().c_str());
			}

			// create the telegram
			Telegram telegram(0, sender, receiver, msg, extraInfo);

			// if there is no delay, route telegram immediately                       
			if (delay <= 0.0)                                                        
			{
				#ifdef _DEBUG
				std::wostringstream s;
				s << "\nTelegram dispatched at time: " << time.TotalTime // Get current frame
				  << " by " << sender << " for " << receiver 
				  << ". Msg is " << msg << "";
				#endif

				// send the telegram to the recipient
				Discharge(receiverEnt, telegram);
			}
			else
			{
				// TODO: handle timed messages
			}

		}

	}
}