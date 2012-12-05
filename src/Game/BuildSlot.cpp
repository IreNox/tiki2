#include "Game/BuildSlot.h"


namespace TikiEngine
{
	namespace AI
	{

		BuildSlot::BuildSlot(GameState* gameState, GameObject* gameObject)
			: Component(gameState->GetEngine(), gameObject)
		{
			this->gameState = gameState;
		}

		BuildSlot::~BuildSlot()
		{
		}

	}
}