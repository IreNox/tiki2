#include "Game/BuildSlot.h"


namespace TikiEngine
{
	namespace AI
	{

		BuildSlot::BuildSlot(GameState* gameState, GameObject* gameObject)
			: Component(gameState->GetEngine(), gameObject), enabled(true)
		{
			this->gameState = gameState;
		}

		BuildSlot::~BuildSlot()
		{
		}

		void BuildSlot::Disable()
		{
			enabled = false;
		}

		void BuildSlot::Enable()
		{
			enabled = true;
		}

		bool BuildSlot::Enabled()
		{
			return enabled;
		}
	}
}