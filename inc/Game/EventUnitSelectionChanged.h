#pragma once

#include "Core/Event.h"

namespace TikiEngine
{
	class GameObject;

	namespace Game
	{
		class GameState;

		struct UnitSelectionChangedArgs 
		{
			const List<GameObject*>& SelectedUnits;
			const List<GameObject*>& SelectedSlots;

			UnitSelectionChangedArgs(const List<GameObject*>& selectedUnits, const List<GameObject*>& selectedSlots)
				: SelectedUnits(selectedUnits), SelectedSlots(selectedSlots)
			{
			}
		};

		typedef Event<GameState, UnitSelectionChangedArgs> UnitSelectionChangedEvent;
		typedef EventHandler<GameState, UnitSelectionChangedArgs> UnitSelectionChangedEventHandler;
	}
}