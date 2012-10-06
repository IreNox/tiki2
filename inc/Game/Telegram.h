#pragma once

#include <iostream>
#include <math.h>

namespace TikiEngine
{
	namespace AI
	{
		enum message_type
		{
		  Msg_Blank,
		  Msg_PathReady,
		  Msg_NoPathAvailable,
		  Msg_TakeThatMF, 
		  Msg_YouGotMeYouSOB,
		  Msg_GoalQueueEmpty,
		  Msg_OpenSesame,
		  Msg_UserHasRemovedBot
		};
		
		/* A telegram is a data structure that records information required to dispatch messages. 
		 * Messages are used by bots to communicate with each other.
		 */
		struct Telegram
		{
			// the entity that sent this telegram
			int Sender;

			// the entity that is to receive this telegram
			int Receiver;

			// the message itself. These are all enumerated in message_type
			int Msg;

			// messages can be dispatched immediately or delayed for a specified amount
			// of time. If a delay is necessary this field is stamped with the time 
			// the message should be dispatched.
			double DispatchTime;

			// any additional information that may accompany the message
			void* ExtraInfo;

			Telegram()
			{
				DispatchTime = -1;
				Sender = -1;
				Receiver = -1;
				Msg = -1;
			}

			Telegram(double time, int sender, int receiver, int msg, void* info = 0)
			{
				this->DispatchTime = time;
				this->Sender = sender;
				this->Receiver = receiver;
				this->Msg = msg;
				this->ExtraInfo = info;
			}
		};

	    //these telegrams will be stored in a priority queue. Therefore the >
		//operator needs to be overloaded so that the PQ can sort the telegrams
		//by time priority. Note how the times must be smaller than
		//SmallestDelay apart before two Telegrams are considered unique.
		const double SmallestDelay = 0.25;

		inline bool operator==(const Telegram& t1, const Telegram& t2)
		{
			return ( fabs(t1.DispatchTime-t2.DispatchTime) < SmallestDelay) &&
					(t1.Sender == t2.Sender)        &&
					(t1.Receiver == t2.Receiver)    &&
					(t1.Msg == t2.Msg);
		}

		inline bool operator<(const Telegram& t1, const Telegram& t2)
		{
			if (t1 == t2)
				return false;
			else
				return (t1.DispatchTime < t2.DispatchTime);
		}

		inline std::ostream& operator<<(std::ostream& os, const Telegram& t)
		{
			os << "time: " << t.DispatchTime << "  Sender: " << t.Sender
			   << "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;
			return os;
		}

		//handy helper function for dereferencing the ExtraInfo field of the Telegram to the required type.
		template <class T>
		inline T DereferenceToType(void* p)
		{
			return *(T*)(p);
		}

	}
}