#pragma once

namespace TikiEngine
{
	template<class T, typename TArgs>
	class EventHandler
	{
	public:

		virtual void Handle(T* sender, const TArgs& args) = 0;

	};
}