#include "Core/IModel.h"
#include "Game/Utils.h"

#include "Game/AnimationHandlerSpidermine.h"


namespace TikiEngine
{
	AnimationHandlerSpidermine::AnimationHandlerSpidermine(IModel* model)
		: model(model)
	{
		this->idle = model->GetAnimation("idle01");
		this->run = model->GetAnimation("run");

		this->idle->SetDuration(2.0);
		this->run->SetDuration(0.75);
	}

	AnimationHandlerSpidermine::~AnimationHandlerSpidermine()
	{
	}

	void AnimationHandlerSpidermine::FindMappedAnimation(AnimationArgs& args)
	{
		float random = RandFloat();

		IAnimation* anim = 0;

		switch(args.animationType)
		{
		case AT_Idle:
			anim = this->idle;
			break;

		case AT_Run:
			anim = this->run;
			break;

		default:
			break;
		}

		args.animation = anim;
	}
}
