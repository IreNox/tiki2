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

	void AnimationHandlerHero::FindMappedAnimation(AnimationArgs& args)
	{
		IAnimation* anim = 0;
		switch(args.animationType)
		{
		case AT_Idle:
			anim = this->idle;
			break;
		case AT_Run:
			anim = this->run;
			break;
		case AT_Attack:
			anim = this->attack;
			break;
		default:
			break;
		}
		args.animation = anim;
	}
}
