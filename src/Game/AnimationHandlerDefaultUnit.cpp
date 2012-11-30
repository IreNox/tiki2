#include "Game/AnimationHandlerDefaultUnit.h"
#include "Core/IModel.h"


namespace TikiEngine
{
	AnimationHandlerDefaultUnit::AnimationHandlerDefaultUnit(IModel* model) : AnimationHandler(model)
	{
		this->walk = model->GetAnimation("walk");
		this->attack = model->GetAnimation("attack");
		this->run = model->GetAnimation("run");

	}
	AnimationHandlerDefaultUnit::~AnimationHandlerDefaultUnit()
	{

	}

	void AnimationHandlerDefaultUnit::Handle(IModel* model, const AnimationArgs& args)
	{
		switch(args.animationType)
		{
		case Walk:
			model->BlendToAnimation(this->walk);
			break;
		case Attack:
			model->BlendToAnimation(this->attack);
			break;
		case Run:
			model->BlendToAnimation(this->run);
			break;
		default:
			break;
		}
	}
}