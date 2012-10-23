#pragma once

#include "Core/RectangleF.h"
#include "Core/UpdateArgs.h"
#include "Game/GameState.h"
#include "Core/GUIButton.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::UserInterface;

		class UnitSelection
		{

		public:
			UnitSelection(GameState* gameState);
			~UnitSelection();

			List<GameObject*>* GetSelectedUnits();

			void Update(const UpdateArgs& args);
			void Draw(const DrawArgs& args);
			
		private:

			Vector2 selectionStartPoint;
			RectangleF selectionRect;

			GameState* gameState;
			List<GameObject*> selectedUnits;

			GUIButton* selectButton;
		};

	}
}