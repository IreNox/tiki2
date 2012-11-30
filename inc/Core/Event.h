#pragma once

#include "Core/EventHandler.h"

namespace TikiEngine
{
	template <class T, typename TArgs>
	class Event
	{
	public:
		void RaiseEvent(T* sender, const TArgs& args) const
		{
			UInt32 i = 0;
			while (i < eventHandler.Count())
			{
				eventHandler[i]->Handle(sender, args);
				i++;
			}
		}

		void SetHandlerOnly(EventHandler<T, TArgs>* handler)
		{
			for(int i = 0; i < eventHandler.Count(); i++)
			{
				SafeDelete(&eventHandler[i]);
			}
			eventHandler.Clear();
			eventHandler.Add(handler);
		}

		void AddHandler(EventHandler<T, TArgs>* handler)
		{
			eventHandler.Add(handler);
			handler->handled.Add(this);
		}

		void RemoveHandler(EventHandler<T, TArgs>* handler)
		{
			eventHandler.Remove(handler);
		}

	protected:

		List<EventHandler<T, TArgs>*> eventHandler;

	};
}