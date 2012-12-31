#pragma once

#include "Core/EngineObject.h"

#include "Core/GUILabel.h"
#include "Core/GUIImage.h"
#include "Core/GUIButton.h"
#include "Core/GUIWindow.h"

#include "Core/EventControls.h"
#include "Core/EventScreenSizeChanged.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::UserInterface;

		class GameState;

		class GameHud : public EngineObject, public ScreenSizeChangedEventHandler, public ClickEventHandler
		{
		public:

			GameHud(GameState* state);
			~GameHud();

			void ResetScreen();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			void Handle(IGraphics* sender, const ScreenSizeChangedArgs& args);
			void Handle(GUIControl* sender, const ClickEventArgs& args);

		private:

			GameState* gameState;

			GUILabel* labelRes;

			GUIButton* buttonMenu;
			GUIWindow* windowResources;
			
			GUIWindow* windowSkills;
			GUIWindow* windowSkillUpgrades;

			List<GUIControl*> enabledControls;

		};
	}
}