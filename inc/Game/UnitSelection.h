#pragma once

#include "Core/RectangleF.h"
#include "Core/UpdateArgs.h"
#include "Core/GUIButton.h"

#include "Game/GameState.h"

#include "Game/TikiBot.h"
#include "Game/BuildSlot.h"

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

			void BuildCommand(BuildSlot* slot);
			void MoveCommand(TikiBot* target, const Vector3& pos, bool attackMove, bool addWaypoint);

			inline bool GetEnabled() { return enabled; }
			inline void SetEnabled(bool val) { enabled = val; }

			List<GameObject*>* GetSelectedUnits();
			List<GameObject*>* GetSelectedSlots();

			void Update(const UpdateArgs& args);
			void Draw(const DrawArgs& args);
			
		private:

			void HandleTikiBot(GameObject* go);
			void HandleBuildSlot(GameObject* go);
			void HandleSelection(GameObject* go);

			bool IsUnderMouse(GameObject* go, Matrix& worldToScreen, float eps = 15);

			void RemoveBot(TikiBot* bot/*, UInt32 index*/);
			
			bool enabled;

			bool dirty;

			Vector2 selectionStartPoint;
			RectangleF selectionRect;

			GameState* gameState;
			List<GameObject*> selectedUnits;
			List<GameObject*> selectedSlots;

			Matrix worldToScreen;
			bool mouseButton;
			bool changed;

			GUIButton* selectButton;

			bool newDragging;
			
			Frustum selectionFrustum;
		};

	}
}