#pragma once

#include "Core/IAnimation.h"
#include "Core/EventAnimation.h"

namespace TikiEngine
{
	class AnimationHandlerHero : public AnimationEventHandler
	{
	public:

		AnimationHandlerHero(IModel* model);
		~AnimationHandlerHero();

		void Handle(IModel* model, const AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* attack;
		IAnimation* run;
		IAnimation* idle;

	};
}