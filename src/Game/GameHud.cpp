
#include "Game/GameHud.h"
#include "Game/GameState.h"

#include "Core/IGraphics.h"
#include "Core/IContentManager.h"

#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		GameHud::GameHud(GameState* state)
			: EngineObject(state->GetEngine()), state(state)
		{
			buttonMenu = new GUIButton(engine);
			buttonMenu->SPosition() = Vector2(25, -5);
			buttonMenu->Text() = L"Menu";
			buttonMenu->SSize() = Vector2(75, 35);
			buttonMenu->AddRef();
			enabledControls.Add(buttonMenu);

			windowResources = new GUIWindow(engine);
			windowResources->SSize() = Vector2(175, 35);
			windowResources->AddRef();
			enabledControls.Add(windowResources);

			GUIImage* image = new GUIImage(engine);
			image->SetTexture(engine->content->LoadTexture(L"hud/mass"));
			image->SSize() = Vector2(16, 16);
			image->SPosition() = Vector2(16, 10);
			windowResources->AddChild(image);

			GUILabel* label = new GUILabel(engine);
			label->Text() = L"0/2500";
			label->SPosition() = Vector2(32, 10);
			windowResources->AddChild(label);

			engine->graphics->ScreenSizeChanged.AddHandler(this);
			this->ResetScreen();
		}

		GameHud::~GameHud()
		{
			SafeRelease(&buttonMenu);
			SafeRelease(&windowResources);

			/*SafeRelease(&texRes1);
			SafeRelease(&imageRes1);
			SafeRelease(&labelRes1);

			SafeRelease(&texRes2);
			SafeRelease(&imageRes2);
			SafeRelease(&labelRes2);*/
		}
		#pragma endregion

		#pragma region Member - ResetScreen
		void GameHud::ResetScreen()
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			windowResources->SPosition() = Vector2((float)vp->Width - 200, -10);

			//imageRes1->SPosition() = Vector2((float)vp->Width - 200, 10);
			//labelRes1->SPosition() = Vector2((float)vp->Width - 180, 10);

			//imageRes2->SPosition() = Vector2((float)vp->Width - 100, 10);
			//labelRes2->SPosition() = Vector2((float)vp->Width - 80, 10);
		}

		void GameHud::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			this->ResetScreen();
		}

		void GameHud::Handle(GUIControl* sender, const ClickEventArgs& args)
		{

		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void GameHud::Draw(const DrawArgs& args)
		{
			UInt32 i = 0;
			while (i < enabledControls.Count())
			{
				enabledControls[i]->Draw(args);

				i++;
			}
		}

		void GameHud::Update(const UpdateArgs& args)
		{
			//wostringstream str;
			//str << state->GetResource1() << L"/" << 1000;
			//labelRes1->Text() = str.str();

			//str = wostringstream();
			//str << state->GetResource2() << L"/" << 100;
			//labelRes2->Text() = str.str();

			UInt32 i = 0;
			while (i < enabledControls.Count())
			{
				enabledControls[i]->Update(args);

				i++;
			}
		}
		#pragma endregion
	}
}
