#pragma once

#include "Core/EventAnimation.h"

namespace TikiEngine
{
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

	//class AnimationHandler : public AnimationEventHandler 
	//{
	//public:
	//	AnimationHandler(IModel* model) { }
	//	~AnimationHandler() { }

	//	virtual void Handle(IModel* model, const AnimationEvent& args) { }

	//private:
	//	IModel* model;
	//};
}