#include "Game/BotRemove.h"
#include "Game/SceneLevel.h"

namespace TikiEngine
{
	namespace AI
	{


		BotRemove::BotRemove(GameState* gameState, GameObject* gameObject)
			: Component(gameState->GetEngine(), gameObject)
		{
			this->gameState = gameState;
			timeTillDeath = 0.0f;

			gameObject->GModel()->AnimationHandler.RaiseEvent(
				gameObject->GModel(),
				AnimationArgs(AT_Death)
			);
		}
		
		const double DeathAnimationLength = 2.0f;

		void BotRemove::Update(const UpdateArgs& args)
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