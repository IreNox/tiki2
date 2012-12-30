
#include "Game/GameHud.h"
#include "Game/GameState.h"

#include "Game/TikiBot.h"
#include "Game/PlayerBase.h"
#include "Game/SkillSystem.h"

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
			: EngineObject(state->GetEngine()), gameState(state)
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

			labelRes = new GUILabel(engine);
			labelRes->Text() = L"0";
			labelRes->SPosition() = Vector2(35, 20);
			windowResources->AddChild(labelRes);

			windowFunc = new GUIWindow(engine);
			windowFunc->SSize() = Vector2(225, 225);
			//enabledControls.Add(windowFunc);

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

			windowSkills = new GUIWindow(engine);
			windowSkills->SSize() = Vector2(295, 90);
			enabledControls.Add(windowSkills);

			i = 0;
			while (i < 4)
			{
				GUIButton* cmd = new GUIButton(engine);
				cmd->SSize() = Vector2(70, 70);
				cmd->SPosition() = Vector2(10.0f + (i * 68), 10.0f);
				cmd->Click.AddHandler(this);

				windowSkills->AddChild(cmd);

				i++;
			}

			engine->graphics->ScreenSizeChanged.AddHandler(this);
			this->ResetScreen();
		}

		GameHud::~GameHud()
		{
			SafeRelease(&buttonMenu);
			SafeRelease(&windowFunc);
			SafeRelease(&windowSkills);
			SafeRelease(&windowResources);
		}
		#pragma endregion

		#pragma region Member - ResetScreen
		void GameHud::ResetScreen()
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			windowFunc->SPosition() = vp->GetSize() - Vector2(220, 220);
			windowSkills->SPosition() = Vector2(100, (float)vp->Height - 90);
			windowResources->SPosition() = Vector2((float)vp->Width - 200, -15.0f);
		}

		void GameHud::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			this->ResetScreen();
		}

		void GameHud::Handle(GUIControl* sender, const ClickEventArgs& args)
		{
			if (sender->GetParent() == windowSkills)
			{
				Int32 index = windowSkills->ChildControls().IndexOf(sender);

				if (index != -1)
				{
					gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys()->GetSkills().Get(index)->Aktivate();
				}
			}
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

			i = 0;
			SkillSystem* sys = gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys();
			while (i < 4)
			{
				args.SpriteBatch->Draw(
					sys->GetSkills().Get(i)->GetIconTexture(),
					windowSkills->ChildControls().Get(i)->GetBoundingBox().Position() + Vector2(13.0f),
					0.0f,
					Vector2::Zero,
					0.35f,
					1.0f
				);

				i++;
			}
		}

		void GameHud::Update(const UpdateArgs& args)
		{
			wostringstream s;
			s << gameState->GetResource();
			labelRes->Text() = s.str();

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
