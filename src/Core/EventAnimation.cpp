#include "Core/IModel.h"
#include "Core/EventAnimation.h"

namespace TikiEngine
{
	using namespace Resources;

	void AnimationEventHandler::Handle(IModel* sender, const AnimationArgs& args)
	{
		if(args.animation)
		{
			sender->BlendToAnimation(args.animation);
		}
	}
}