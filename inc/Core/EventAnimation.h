#pragma once

#include "Core/Event.h"
#include "Core/TypeGlobals.h"

namespace TikiEngine
{
	namespace Resources
	{
		class IModel;
	}
	using namespace Resources;

	enum AnimationType
	{
		AT_Idle,
		AT_Walk,
		AT_Attack,
		AT_Run,
		AT_Death
	};
	
	struct AnimationArgs
	{
		AnimationType animationType;
		AnimationArgs(AnimationType type = AT_Run) : animationType(type) {}
	};

	class AnimationEvent: public Event<IModel, AnimationArgs>
	{
	public:
		~AnimationEvent()
		{
			for(UINT i = 0; i < eventHandler.Count(); i++)
				SafeDelete(&eventHandler[i]);
		}
	};

	//typedef Event<IModel, AnimationArgs> AnimationEvent;
	typedef EventHandler<IModel, AnimationArgs> AnimationEventHandler;
}