#pragma once

#include "Core/EngineObject.h"

#include "Core/GUILabel.h"
#include "Core/GUIImage.h"
#include "Core/GUIButton.h"
#include "Core/GUICustomButton.h"

#include "Game/HUDFunctionList.h"

#include "Game/UnitFunctions.h"

#include "Core/EventScreenSizeChanged.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::UserInterface;

		class GameState;

		class GameHud : public EngineObject, public ScreenSizeChangedEventHandler
		{
		public:

			GameHud(GameState* state);
			~GameHud();

			void ResetScreen();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			void Handle(IGraphics* sender, const ScreenSizeChangedArgs& args);

		private:

			GameState* state;

			GUICustomButton* buttonMenu;
			
			ITexture* texRes1;
			GUIImage* imageRes1;
			GUILabel* labelRes1;

			ITexture* texRes2;
			GUIImage* imageRes2;
			GUILabel* labelRes2;
			
			Dictionary<UnitFunctions, GUIButton*> funcButton;

			List<GUIControl*> enabledControls;

		};
	}
}