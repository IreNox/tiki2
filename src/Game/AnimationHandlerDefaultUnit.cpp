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
		//this->attack->SetLoop(false);
		//this->attack->SetNextAnimation(this->idle);

		this->run->SetDuration(0.75); 

		this->death1->SetDuration(1.0);
		this->death1->SetPriority(1);

		this->death2->SetDuration(1.5);
		this->death2->SetPriority(1);
		this->death2->SetLoop(false);

		this->idle->SetDuration(2.0);


	}
	AnimationHandlerDefaultUnit::~AnimationHandlerDefaultUnit()
	{
	}

	void AnimationHandlerDefaultUnit::FindMappedAnimation(AnimationArgs& args)
	{
		float random = RandFloat();

		IAnimation* anim = 0;

		switch(args.animationType)
		{
		case AT_Idle:
			anim = this->idle;
			break;

		case AT_Walk:
			anim = this->walk;
			break;

		case AT_Run:
			anim = this->run;
			break;

		case AT_Attack:
			anim = this->attack;
			break;

		case AT_Death:
			if(random <= 0.5f)
				anim = this->death1;
			else
				anim = this->death2;
			break;

		default:
			break;
		}

		args.animation = anim;
	}

	//void AnimationHandlerDefaultUnit::Handle(IModel* model, const AnimationArgs& args)
	//{
	//	float random = RandFloat();

	//	IAnimation* anim = 0;

	//	switch(args.animationType)
	//	{
	//	case AT_Idle:
	//		anim = this->idle;
	//		break;

	//	case AT_Walk:
	//		anim = this->walk;
	//		break;

	//	case AT_Run:
	//		anim = this->run;
	//		break;

	//	case AT_Attack:
	//		anim = this->attack;
	//		break;

	//	case AT_Death:
	//		if(random <= 0.5f)
	//			anim = this->death1;
	//		else
	//			anim = this->death2;
	//		break;

	//	default:
	//		break;
	//	}

	//	if(anim)
	//	{
	//		model->BlendToAnimation(anim);
	//		//args.animation = anim;
	//	}

	//}
}
