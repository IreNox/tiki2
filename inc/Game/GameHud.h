#pragma once

#include "Core/GUILabel.h"
#include "Core/GUIImage.h"
#include "Core/GUIButton.h"
#include "Core/GUICustomButton.h"

#include "Game/UnitFunctions.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::UserInterface;

		class GameState;

		class GameHud
		{
		public:

			GameHud(GameState* state);
			~GameHud();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			GameState* state;

			GUICustomButton* buttonMenu;
			
			GUIImage* imageRes1;
			GUILabel* labelRes1;

			GUIImage* imageRes2;
			GUILabel* labelRes2;
			
			Dictionary<UnitFunctions, GUIButton*> funcButton;

			List<GUIControl*> enabledControls;

		};
	}
}