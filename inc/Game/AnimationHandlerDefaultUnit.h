#pragma once

#include "Core/IAnimation.h"
#include "Core/EventAnimation.h"

namespace TikiEngine
{
	class AnimationHandlerDefaultUnit : public AnimationEventHandler
	{
	public:

		AnimationHandlerDefaultUnit(IModel* model);
		~AnimationHandlerDefaultUnit();

		void Handle(IModel* model, const AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* walk;
		IAnimation* attack;
		IAnimation* run;
		IAnimation* death1;
		IAnimation* death2;
		IAnimation* idle;
	};
}