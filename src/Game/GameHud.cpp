
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
			buttonMenu->SPosition() = Vector2(20, -15);
			buttonMenu->Text() = L"Menu";
			buttonMenu->SSize() = Vector2(100, 55);
			buttonMenu->AddRef();
			buttonMenu->Click.AddHandler(this);
			enabledControls.Add(buttonMenu);

			windowResources = new GUIWindow(engine);
			windowResources->SSize() = Vector2(180, 55);
			windowResources->AddRef();
			enabledControls.Add(windowResources);

			GUIImage* image = new GUIImage(engine);
			image->SetTexture(engine->content->LoadTexture(L"hud/mass"));
			image->SSize() = Vector2(16, 16);
			image->SPosition() = Vector2(16, 20);
			windowResources->AddChild(image);

			GUILabel* label = new GUILabel(engine);
			label->Text() = L"0/2500";
			label->SPosition() = Vector2(35, 20);
			windowResources->AddChild(label);

			windowFunc = new GUIWindow(engine);
			windowFunc->SSize() = Vector2(225, 225);
			enabledControls.Add(windowFunc);

			UInt32 i = 0;
			while (i < 9)
			{
				int x = i % 3;
				int y = i / 3;

				GUIButton* cmd = new GUIButton(engine);
				cmd->SSize() = Vector2(70, 70);
				cmd->SPosition() = Vector2(
					10.0f + (x * 68),
					10.0f + (y * 68)
				);
				windowFunc->AddChild(cmd);

				i++;
			}

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

			windowFunc->SPosition() = Vector2((float)vp->Width - 220, (float)vp->Height - 220);
			windowResources->SPosition() = Vector2((float)vp->Width - 200, -15);

			//UInt32 i = 0;
			//while (i < windowResources->ChildControls().Count())
			//{
			//	windowResources->ChildControls()[i]->SPosition() = Vector2(10, 10);
			//	i++;
			//}

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
