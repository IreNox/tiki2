#pragma once

#include "Core/IAnimation.h"
#include "Core/EventAnimation.h"

namespace TikiEngine
{
	class AnimationHandlerSpidermine : public AnimationEvent
	{
	public:

		AnimationHandlerSpidermine(IModel* model);
		~AnimationHandlerSpidermine();

		void FindMappedAnimation(AnimationArgs& args);

	private:

		IModel* model;

		IAnimation* idle;
		IAnimation* run;
	};
}