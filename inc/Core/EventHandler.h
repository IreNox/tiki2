#pragma once

#include "Core/List.h"

namespace TikiEngine
{
	template<class T, typename TArgs>
	class Event;

	template<class T, typename TArgs>
	class EventHandler
	{
		friend class Event<T, TArgs>;

	public:

		EventHandler() {}
		virtual ~EventHandler()
		{
			UInt32 i = 0;
			while (i < handled.Count())
			{
				handled[i]->RemoveHandler(this);
				i++;
			}
		}

		virtual void Handle(T* sender, const TArgs& args) = 0;

	private:

		List<Event<T, TArgs>*> handled;

	};
}