#pragma once

#include "Core/Event.h"
#include "Core/IModel.h"

namespace TikiEngine
{

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

	typedef Event<IModel, AnimationArgs> AnimationEvent;
	typedef EventHandler<IModel, AnimationArgs> AnimationEventHandler;
}