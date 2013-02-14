#include "Game/AnimationHandler.h"

#include "Core/IModel.h"
#include "Game/Utils.h"

namespace TikiEngine
{
#pragma region MG
	AnimationHandlerMGUnit::AnimationHandlerMGUnit(IModel* model)
		: model(model), attack(0), run(0), death(0), idle(0)
	{


		this->attack = model->GetAnimation("attackmg");
		this->run = model->GetAnimation("runmg");
		this->death = model->GetAnimation("death01");
		this->idle = model->GetAnimation("idle01");

		this->attack->SetDuration(0.21);
		this->attack->SetLoop();
		this->attack->SetNextAnimation(this->idle);

		this->run->SetDuration(0.75); 

		this->death->SetDuration(1.5);
		this->death->SetPriority(1);
		this->death->SetLoop();

		this->idle->SetDuration(2.0);


	}
	AnimationHandlerMGUnit::~AnimationHandlerMGUnit()
	{
	}

	void AnimationHandlerMGUnit::FindMappedAnimation(AnimationArgs& args)
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

		case AT_Death:
			anim = this->death;
			break;

		default:
			break;
		}

		args.animation = anim;
	}
#pragma  endregion

#pragma region Plasma
	AnimationHandlerPlasmaUnit::AnimationHandlerPlasmaUnit(IModel* model)
		: model(model), attack(0), run(0), death(0), idle(0)
	{
		this->attack = model->GetAnimation("attackheavy");
		this->run = model->GetAnimation("runheavy");
		this->death = model->GetAnimation("death01");
		this->idle = model->GetAnimation("idle01");

		this->attack->SetDuration(1.0);
		this->attack->SetLoop();
		this->attack->SetNextAnimation(this->idle);

		this->run->SetDuration(0.75); 

		this->death->SetDuration(1.5);
		this->death->SetPriority(1);
		this->death->SetLoop();

		this->idle->SetDuration(2.0);


	}
	AnimationHandlerPlasmaUnit::~AnimationHandlerPlasmaUnit()
	{
	}

	void AnimationHandlerPlasmaUnit::FindMappedAnimation(AnimationArgs& args)
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

		case AT_Death:
			anim = this->death;
			break;

		default:
			break;
		}

		args.animation = anim;
	}
#pragma endregion

#pragma region Hero
	AnimationHandlerHero::AnimationHandlerHero(IModel* model)
		: model(model), attack(0), run(0), idle1(0), idle2(0), idle3(0),
		death1(0), death2(0), rocket(0)
	{
		this->attack = model->GetAnimation("attackgattling");
		this->run = model->GetAnimation("run");

		this->idle1 = model->GetAnimation("idle01");
		this->idle2 = model->GetAnimation("idle02");
		this->idle3 = model->GetAnimation("idle03");

		this->death1 = model->GetAnimation("death01");
		this->death2 = model->GetAnimation("death02");

		this->rocket = model->GetAnimation("rocket");

		this->attack->SetDuration(0.65);
		this->attack->SetLoop();
		this->attack->SetNextAnimation(this->idle2);

		this->idle1->SetDuration(2.5);
		this->idle1->SetLoop();
		this->idle1->SetNextAnimation(this->idle2);

		this->idle2->SetDuration(2.0);
		this->idle2->SetLoop(3);
		this->idle2->SetNextAnimation(this->idle3);

		this->idle3->SetDuration(5.0);
		this->idle3->SetLoop();
		this->idle3->SetNextAnimation(this->idle1);

		this->rocket->SetDuration(1.5);
		this->rocket->SetLoop();
		this->rocket->SetNextAnimation(this->idle2);

		this->death1->SetDuration(1.5);
		this->death2->SetDuration(1.5);

		this->run->SetDuration(1.0); 
		

	}
	AnimationHandlerHero::~AnimationHandlerHero()
	{
	}

	void AnimationHandlerHero::FindMappedAnimation(AnimationArgs& args)
	{
		float random = RandFloat();

		IAnimation* anim = 0;
		switch(args.animationType)
		{
		case AT_Idle:
			if(random <= 0.1f)
			{
				anim = this->idle1;
			}else if( random <= 0.2f)
			{
				anim = this->idle3;
			}
			else
			{
				anim = this->idle2;
			}
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

		case AT_Rocket:
			anim = this->rocket;
			break;

		default:
			break;
		}
		args.animation = anim;
	}
#pragma endregion

#pragma region Spidermine
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
#pragma endregion

#pragma region Base
	AnimationHandlerPlayerBase::AnimationHandlerPlayerBase(IModel* model)
		: model(model), idle(0), folding(0), folded(0), unfolding(0)
	{
		this->idle = model->GetAnimation("idle"); //
		this->folding = model->GetAnimation("folding");
		this->folded = model->GetAnimation("folded");
		this->unfolding = model->GetAnimation("unfolding");

		this->idle->SetDuration(18.0);
		this->idle->SetLoop();
		this->idle->SetNextAnimation(this->folding);

		this->folding->SetDuration(2.0);
		this->folding->SetLoop();
		this->folding->SetNextAnimation(this->folded);

		this->folded->SetDuration(5.0);
		this->folded->SetLoop();
		this->folded->SetNextAnimation(this->unfolding);

		this->unfolding->SetDuration(2.0);
		this->unfolding->SetLoop();
		this->unfolding->SetNextAnimation(this->idle);

	}

	AnimationHandlerPlayerBase::~AnimationHandlerPlayerBase()
	{
	}

	void AnimationHandlerPlayerBase::FindMappedAnimation(AnimationArgs& args)
	{
		float random = RandFloat();

		IAnimation* anim = 0;

		switch(args.animationType)
		{
		case AT_Idle:
			anim = this->idle;
			break;

		case AT_Folding:
			anim = this->folding;
			break;

		case AT_Folded:
			anim = this->folded;
			break;

		case AT_UnFolding:
			anim = this->unfolding;
			break;
			//IAnimation* idle;
			//IAnimation* folding;
			//IAnimation* folded;
			//IAnimation* unfolding;

		default:
			break;
		}

		args.animation = anim;
	}
#pragma endregion

#pragma region Research
	AnimationHandlerResearchBuilding::AnimationHandlerResearchBuilding(IModel* model)
		: model(model), idle(0), closing(0), opening(0), research(0)
	{
		this->idle = model->GetAnimation("idle"); 
		this->closing = model->GetAnimation("closing");
		this->opening = model->GetAnimation("opening");
		this->research = model->GetAnimation("research");

		idle->SetDuration(0.66);
		idle->SetLoop();
		idle->SetNextAnimation(opening);

		opening->SetDuration(2.0);
		opening->SetLoop();
		opening->SetNextAnimation(research);

		research->SetDuration(6.0);
		research->SetLoop();
		research->SetNextAnimation(closing);

		closing->SetDuration(2.0);
		closing->SetLoop();
		closing->SetNextAnimation(idle);

	}

	AnimationHandlerResearchBuilding::~AnimationHandlerResearchBuilding()
	{
	}

	void AnimationHandlerResearchBuilding::FindMappedAnimation(AnimationArgs& args)
	{
	}
#pragma endregion

#pragma region Spawn
	AnimationHandlerSpawn::AnimationHandlerSpawn(IModel* model)
		: model(model), idleopen(0), idleclosed(0), closing(0), opening(0)
	{

		this->idleopen = model->GetAnimation("idleopened");
		this->idleclosed = model->GetAnimation("idleclosed");
		this->closing = model->GetAnimation("closing");
		this->opening = model->GetAnimation("opening");


		idleopen->SetLoop(3);
		idleopen->SetNextAnimation(closing);

		closing->SetLoop();
		closing->SetNextAnimation(idleclosed);

		idleclosed->SetLoop();
		idleclosed->SetNextAnimation(opening);

		opening->SetLoop();
		opening->SetNextAnimation(idleopen);
	}

	AnimationHandlerSpawn::~AnimationHandlerSpawn()
	{
	}

	void AnimationHandlerSpawn::FindMappedAnimation(AnimationArgs& args)
	{
	}
#pragma  endregion

}