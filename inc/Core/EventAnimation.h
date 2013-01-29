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
		Idle,
		Walk,
		Attack,
		Run,
		Death
	};
	
	struct AnimationArgs
	{
		AnimationType animationType;
		AnimationArgs(AnimationType type = Run) : animationType(type) {}
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