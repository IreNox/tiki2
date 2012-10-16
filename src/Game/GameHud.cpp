
#include "Game/GameHud.h"
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		GameHud::GameHud(GameState* state)
			: state(state)
		{
			//buttonMenu

			imageRes1 = new GUIImage(state->GetEngine());
			//imageRes1->SetTexture()

			labelRes1 = new GUILabel(state->GetEngine());
			labelRes1->Text() = L"100/2500";

			GUIImage* imageRes2;
			GUILabel* labelRes2;
		}

		GameHud::~GameHud()
		{

		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void GameHud::Draw(const DrawArgs& args)
		{

		}

		void GameHud::Update(const UpdateArgs& args)
		{

		}
		#pragma endregion
	}
}
