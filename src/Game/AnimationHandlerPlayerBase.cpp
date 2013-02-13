#include "Core/IModel.h"
#include "Game/Utils.h"

#include "Game/AnimationHandlerPlayerBase.h"


namespace TikiEngine
{
	AnimationHandlerPlayerBase::AnimationHandlerPlayerBase(IModel* model)
		: model(model), idle(0), folding(0), folded(0), unfolding(0)
	{
		this->idle = model->GetAnimation("idle"); //
		this->folding = model->GetAnimation("folding");
		this->folded = model->GetAnimation("folded");
		this->unfolding = model->GetAnimation("unfolding");

		this->idle->SetDuration(18.0);

		this->folding->SetDuration(2.0);
		this->folding->SetLoop(false);
		this->folding->SetNextAnimation(this->folded);

		this->folded->SetDuration(2.0);

		this->unfolding->SetDuration(2.0);
		this->unfolding->SetLoop(false);
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
}
