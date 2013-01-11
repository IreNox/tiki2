#pragma once

#include "Core/EngineObject.h"

#include "Core/GUILabel.h"
#include "Core/GUIImage.h"
#include "Core/GUIButton.h"
#include "Core/GUIWindow.h"

#include "Game/TikiBot.h"
#include "Game/BuildSlot.h"

#include "Core/EventControls.h"
#include "Core/EventScreenSizeChanged.h"
#include "Game/EventUnitSelectionChanged.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::AI;
		using namespace TikiEngine::UserInterface;

		class GameState;

		class GameHud : public EngineObject, public ScreenSizeChangedEventHandler, public ClickEventHandler, public UnitSelectionChangedEventHandler
		{
		public:

			GameHud(GameState* state);
			~GameHud();

			void Init();

			void ResetScreen();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			void Handle(IGraphics* sender, const ScreenSizeChangedArgs& args);
			void Handle(GUIControl* sender, const ClickEventArgs& args);
			void Handle(GameState* sender, const UnitSelectionChangedArgs& args);

		private:

			GameState* gameState;

			GUILabel* labelRes;

			GUIButton* buttonMenu;
			GUIWindow* windowResources;
			
			GUIWindow* windowSkills;
			GUIWindow* windowSkillUpgrades;

			GUIWindow* windowBuildSlot;

			GUIImage* imgMinimap;

			List<GUIControl*> enabledControls;

			TikiBot* selectedBot;
			BuildSlot* selectedSlot;

			ITexture* texInfo;
			ITexture* texHealth;
			ITexture* texShield;
			
			ITexture* texMinimapMop;
			ITexture* texMinimapHero;

			//void initRes();
			//void initSkills();
			//void initMinimapBot();

		};
	}
}