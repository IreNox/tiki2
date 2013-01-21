#include "Core/IModel.h"
#include "Game/Utils.h"

#include "Game/AnimationHandlerHero.h"

namespace TikiEngine
{
	AnimationHandlerHero::AnimationHandlerHero(IModel* model)
		: model(model)
	{
		this->attack = model->GetAnimation("attack");
		this->attack->SetDuration(0.21);
		this->run = model->GetAnimation("run");
		this->run->SetDuration(0.75); 
		this->idle = model->GetAnimation("idle01");
		this->idle->SetDuration(2.0);

		this->attack->SetLoop(false);
		this->attack->SetNextAnimation(this->idle);

	}
	AnimationHandlerHero::~AnimationHandlerHero()
	{
	}

	void AnimationHandlerHero::Handle(IModel* model, const AnimationArgs& args)
	{
		float random = RandFloat();

		switch(args.animationType)
		{
		case Idle:
			model->BlendToAnimation(this->idle);
			break;
		case Run:
			model->BlendToAnimation(this->run);
			break;
		case Attack:
			model->BlendToAnimation(this->attack);
			break;
		default:
			break;
		}
	}
}
