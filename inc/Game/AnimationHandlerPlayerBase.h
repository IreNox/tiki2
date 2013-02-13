#pragma once

#include "Core/IAnimation.h"
#include "Core/EventAnimation.h"

namespace TikiEngine
{
	class AnimationHandlerPlayerBase : public AnimationEvent
	{
	public:

		AnimationHandlerPlayerBase(IModel* model);
		~AnimationHandlerPlayerBase();

		void FindMappedAnimation(AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* idle;
		IAnimation* folding;
		IAnimation* folded;
		IAnimation* unfolding;
	};
}