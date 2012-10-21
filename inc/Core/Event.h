#pragma once

#include "Core/EventHandler.h"

namespace TikiEngine
{
	template <class T, typename TArgs>
	class Event
	{
	public:

		void RaiseEvent(T* sender, const TArgs& args)
		{
			UInt32 i = 0;
			while (i < eventHandler.Count())
			{
				eventHandler[i]->Handle(sender, args);
				i++;
			}
		}

		void AddHandler(EventHandler<T, TArgs>* handler)
		{
			eventHandler.Add(handler);
		}

		void RemoveHandler(EventHandler<T, TArgs>* handler)
		{
			eventHandler.Remove(handler);
		}

	protected:

		List<EventHandler<T, TArgs>*> eventHandler;

	};
}