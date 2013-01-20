#include "Game/BuildSlot.h"


namespace TikiEngine
{
	namespace AI
	{
		#pragma region Class
		BuildSlot::BuildSlot(GameState* gameState, GameObject* gameObject)
			: Component(gameState->GetEngine(), gameObject), enabled(true)
		{
			this->gameState = gameState;
		}

		BuildSlot::~BuildSlot()
		{
		}
		#pragma endregion

		#pragma region Member
		void BuildSlot::Disable()
		{
			enabled = false;
		}

		void BuildSlot::Enable()
		{
			enabled = true;
		}
		#pragma endregion

		#pragma region Member - Build
		void BuildSlot::BuildTower()
		{

		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void BuildSlot::Draw(const DrawArgs& args)
		{

		}

		void BuildSlot::Update(const UpdateArgs& args)
		{

		}
		#pragma endregion
	}
}