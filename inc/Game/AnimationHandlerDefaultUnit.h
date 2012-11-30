#pragma once

#include "Core/IAnimation.h"
#include "Core/AnimationHandler.h"

namespace TikiEngine
{
	class AnimationHandlerDefaultUnit : public AnimationHandler
	{
	public:
		AnimationHandlerDefaultUnit(IModel* model);
		~AnimationHandlerDefaultUnit();

		void Handle(IModel* model, const AnimationArgs& args);


	private:

		IAnimation* walk;
		IAnimation* attack;
		IAnimation* run;
	};
}