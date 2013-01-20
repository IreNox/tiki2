#include "Game/BaseGameEntity.h"

#include <cassert>

namespace TikiEngine
{
	namespace AI
	{
		int BaseGameEntity::nextValidID = 0;

		BaseGameEntity::BaseGameEntity(GameState* gameState, GameObject* gameObject)
			: Component(gameState->GetEngine(), gameObject), gameState(gameState)
		{
			id = nextValidID++;

			boundingRadius = 2.0;
            type = ET_Default;
            tag = false;
		}
	}
}