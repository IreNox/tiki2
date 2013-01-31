#pragma once

#include "Core/IAnimation.h"
#include "Core/EventAnimation.h"

namespace TikiEngine
{
	class AnimationHandlerHero : public AnimationEvent
	{
	public:

		AnimationHandlerHero(IModel* model);
		~AnimationHandlerHero();

		void FindMappedAnimation(AnimationArgs& args);


	private:

		IModel* model;

		IAnimation* attack;
		IAnimation* run;
		IAnimation* idle;

	};
}