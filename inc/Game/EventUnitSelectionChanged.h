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
			List<GameObject*>* SelectedUnits;

			UnitSelectionChangedArgs(List<GameObject*>* selectedUnits) : SelectedUnits(selectedUnits) {}
		};

		typedef Event<GameState, UnitSelectionChangedArgs> UnitSelectionChangedEvent;
		typedef EventHandler<GameState, UnitSelectionChangedArgs> UnitSelectionChangedEventHandler;
	}
}