#include "Game/BotRemove.h"
#include "Game/SceneLevel.h"

namespace TikiEngine
{
	namespace AI
	{


		BotRemove::BotRemove(GameState* gameState, GameObject* gameObject)
			: Component(gameState->GetEngine(), gameObject), deathAnimation(0)
		{
			this->gameState = gameState;
			timeTillDeath = 0.0f;


			AnimationArgs animArgs(AT_Death);
			gameObject->GModel()->AnimationHandler->RaiseAnimationEvent(
				gameObject->GModel(),animArgs);
			deathAnimation = animArgs.animation;
		}
		
		const double DeathAnimationLength = 2.0f;

		void BotRemove::Update(const UpdateArgs& args)
		{
			if(deathAnimation && deathAnimation->IsFinished())
			{
				gameState->GetScene()->RemoveElement(GetGameObject());
			}
			else
			{
				timeTillDeath += args.Time.ElapsedTime;

				if (timeTillDeath >= DeathAnimationLength)
				{
					gameState->GetScene()->RemoveElement(GetGameObject());
					return;
				}
			}
		}
	}
}