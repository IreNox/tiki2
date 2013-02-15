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

		class GameHudContent
		{
		public:
			GameHudContent();
			~GameHudContent();


		private:
		};

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

			float scale;
			Vector2 vp;

			GUIImage* buttonMenu;
			GUIImage* windowData;
			GUIImage* windowMain;
			GUIImage* windowMinimap;

			GUILabel* labelRes;
			GUIImage* imgMinimap;

			GUIImage* controlBuildSlot;
			GUIControl* controlSkills;
			GUIWindow* controlSkillUpgrades;

			List<GUIControl*> enabledControls;

			TikiBot* selectedBot;
			BuildSlot* selectedSlot;

			ITexture* texInfo;
			ITexture* texHealth;
			ITexture* texShield;
			
			ITexture* texMinimapMop;
			ITexture* texMinimapHero;

			ITexture* texBarHpBg;
			ITexture* texBarHpText;

			ITexture* texBarExpBg;
			ITexture* texBarExpText;

		};
	}
}