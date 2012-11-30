#pragma once

#include "Core/Event.h"

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

	typedef Event<IModel, AnimationArgs> AnimationEvent;
	typedef EventHandler<IModel, AnimationArgs> AnimationEventHandler;
}