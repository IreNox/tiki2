#pragma once

#include "Core/EventAnimation.h"

namespace TikiEngine
{
	namespace Resources
	{
		class IModel;
	}

	using namespace Resources;

	class AnimationHandler : public AnimationEventHandler
	{
	public:
		AnimationHandler(IModel* model) : model(model) { }
		~AnimationHandler() {}

		virtual void Handle(IModel* sender, const AnimationArgs& args) { }

	private:
		IModel* model;
	};
}