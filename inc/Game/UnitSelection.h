#pragma once

#include "Core/RectangleF.h"
#include "Core/UpdateArgs.h"
#include "Core/GUIButton.h"

#include "Game/GameState.h"

#include "Game/TikiBot.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::UserInterface;

		class UnitSelection : public EngineObject
		{
		public:

			UnitSelection(GameState* gameState);
			~UnitSelection();

			List<GameObject*>* GetSelectedUnits();
			List<GameObject*>* GetSelectedSlots();

			void Update(const UpdateArgs& args);
			void Draw(const DrawArgs& args);
			
		private:
			void RemoveBot(TikiBot* bot, UInt32 index);


			Vector2 selectionStartPoint;
			RectangleF selectionRect;

			GameState* gameState;
			List<GameObject*> selectedUnits;

			List<GameObject*> selectedSlots;

			GUIButton* selectButton;
		};

	}
}