#include "Core/IModel.h"
#include "Game/Utils.h"

#include "Game/AnimationHandlerDefaultUnit.h"


namespace TikiEngine
{
	AnimationHandlerDefaultUnit::AnimationHandlerDefaultUnit(IModel* model) : AnimationHandler(model)
	{
		this->walk = model->GetAnimation("walk");
		this->walk->SetDuration(1.0);
		//this->walk->SetDuration(2.0); // 2sekunden
		//this->walk->SetAnimationSpeed(2.0); //zweimal so schnell wie normal
		this->attack = model->GetAnimation("attack");
		this->attack->SetDuration(0.21);
		this->run = model->GetAnimation("run");
		this->run->SetDuration(0.75); 
		this->death1 = model->GetAnimation("death01");
		this->death1->SetDuration(1.0);
		this->death2 = model->GetAnimation("death02");
		this->death2->SetDuration(1.5);
		this->idle = model->GetAnimation("idle");
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

		case Idle:
			model->BlendToAnimation(this->idle);
			break;

		case Walk:
			model->BlendToAnimation(this->walk);
			break;

		case Run:
			model->BlendToAnimation(this->run);
			break;

		case Attack:
			model->BlendToAnimation(this->attack);
			break;

		case Death:
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