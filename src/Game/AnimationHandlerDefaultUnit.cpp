#include "Core/IModel.h"
#include "Game/Utils.h"

#include "Game/AnimationHandlerDefaultUnit.h"


namespace TikiEngine
{
	AnimationHandlerDefaultUnit::AnimationHandlerDefaultUnit(IModel* model)
		: model(model)
	{
		this->walk = model->GetAnimation("walk");
		this->attack = model->GetAnimation("attack");
		this->run = model->GetAnimation("run");
		this->death1 = model->GetAnimation("death01");
		this->death2 = model->GetAnimation("death02");
		this->idle = model->GetAnimation("idle01");

		this->walk->SetDuration(1.0);
		//this->walk->SetDuration(2.0); // 2sekunden
		//this->walk->SetAnimationSpeed(2.0); //zweimal so schnell wie normal

		this->attack->SetDuration(0.21);
		this->attack->SetLoop(false);
		this->attack->SetNextAnimation(this->idle);

		this->run->SetDuration(0.75); 

		this->death1->SetDuration(1.0);

		this->death2->SetDuration(1.5);

		this->idle->SetDuration(2.0);


	}
	AnimationHandlerDefaultUnit::~AnimationHandlerDefaultUnit()
	{
	}

	void AnimationHandlerDefaultUnit::Handle(IModel* model, const AnimationArgs& args)
	{
		float random = RandFloat();

		switch(args.animationType)
		{
		case AT_Idle:
			model->BlendToAnimation(this->idle);
			break;

		case AT_Walk:
			model->BlendToAnimation(this->walk);
			break;

		case AT_Run:
			model->BlendToAnimation(this->run);
			break;

		case AT_Attack:
			model->BlendToAnimation(this->attack);
			break;

		case AT_Death:
			if(random <= 0.5f)
				model->BlendToAnimation(this->death1);
			else
				model->BlendToAnimation(this->death2);
			break;

		default:
			break;
		}
	}
}
