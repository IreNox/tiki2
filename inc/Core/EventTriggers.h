#pragma once

#include "Core/Event.h"

namespace TikiEngine
{
	namespace Components
	{
		class ICollider;
	}

	namespace Modules
	{
		class IPhysics;
	}

	using namespace TikiEngine::Components;

	struct TriggerArgs
	{
		ICollider* triggerCollider;
		ICollider* otherCollider;

		TriggerArgs(ICollider* trigger, ICollider* other)
			: triggerCollider(trigger), otherCollider(other) { }
	};

	struct TriggerEnterArgs : public TriggerArgs
	{
		TriggerEnterArgs(ICollider* trigger, ICollider* other)
			: TriggerArgs(trigger, other) { }
	};

	struct TriggerStayArgs : public TriggerArgs
	{
		TriggerStayArgs(ICollider* trigger, ICollider* other)
			: TriggerArgs(trigger, other) { }
	};

	struct TriggerExitArgs : public TriggerArgs
	{
		TriggerExitArgs(ICollider* trigger, ICollider* other)
			: TriggerArgs(trigger, other) { }
	};

	typedef Event<ICollider, TriggerEnterArgs> TriggerEnterEvent;
	typedef EventHandler<ICollider, TriggerEnterArgs> TriggerEnterEventHandler;

	typedef Event<ICollider, TriggerStayArgs> TriggerStayEvent;
	typedef EventHandler<ICollider, TriggerStayArgs> TriggerStayEventHandler;

	typedef Event<ICollider, TriggerExitArgs> TriggerExitEvent;
	typedef EventHandler<ICollider, TriggerExitArgs> TriggerExitEventHandler;
}