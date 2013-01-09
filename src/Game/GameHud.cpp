
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

			windowSkills = new GUIWindow(engine);
			windowSkills->SSize() = Vector2(295, 90);
			enabledControls.Add(windowSkills);

			UInt32 i = 0;
			while (i < 4)
			{
				GUIButton* cmd = new GUIButton(engine);
				cmd->SSize() = Vector2(70, 70);
				cmd->SPosition() = Vector2(10.0f + (68.0f * i), 10.0f);
				cmd->Click.AddHandler(this);

				windowSkills->AddChild(cmd);

				i++;
			}

			windowSkillUpgrades = new GUIWindow(engine);
			windowSkillUpgrades->SSize() = Vector2(219, 67);

			i = 0;
			while (i < 4)
			{
				GUIButton* cmd = new GUIButton(engine);
				cmd->SSize() = Vector2(48, 48);
				cmd->SPosition() = Vector2(10.0f + (50.0f * i), 10.0f);
				cmd->Text() = L"+";
				cmd->Click.AddHandler(this);

				windowSkillUpgrades->AddChild(cmd);

				i++;
			}
			
			engine->graphics->ScreenSizeChanged.AddHandler(this);
			this->ResetScreen();
		}

		GameHud::~GameHud()
		{
			SafeRelease(&buttonMenu);

			SafeRelease(&windowSkills);
			SafeRelease(&windowSkillUpgrades);

			SafeRelease(&windowResources);
		}
		#pragma endregion

		#pragma region Member - Click
		void GameHud::Handle(GUIControl* sender, const ClickEventArgs& args)
		{
			if (sender == buttonMenu)
			{
				//engine->SetScene()
			}
			else if (sender->GetParent() == windowSkills)
			{
				Int32 index = windowSkills->ChildControls().IndexOf(sender);

				if (index != -1)
				{
					gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys()->GetSkills().Get(index)->Aktivate();
				}
			}
			else if (sender->GetParent() == windowSkillUpgrades)
			{
				Int32 index = windowSkillUpgrades->ChildControls().IndexOf(sender);
				
				if (index != -1)
				{
					SkillSystem* sys = gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys();
					sys->UpgradeSkill(index);

					Skill* skill = sys->GetSkills().Get(index);
					if (skill->GetCurrentLevel() == skill->GetDesc().MaxLevel)
					{
						windowSkillUpgrades->RemoveChild(sender);
					}
				}
			}
		}
		#pragma endregion

		#pragma region Member - ResetScreen
		void GameHud::ResetScreen()
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			windowSkills->SPosition() = Vector2(100, (float)vp->Height - 90);
			windowSkillUpgrades->SPosition() = Vector2(140, (float)vp->Height - 150);
			windowResources->SPosition() = Vector2((float)vp->Width - 200, -15.0f);
		}

		void GameHud::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			this->ResetScreen();
		}
		#pragma endregion
		
		#pragma region Member - Draw
		void GameHud::Draw(const DrawArgs& args)
		{
			UInt32 i = 0;
			while (i < enabledControls.Count())
			{
				enabledControls[i]->Draw(args);

				i++;
			}

			SkillSystem* sys = gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys();

			if (sys->GetSkillUpgrades() > 0)
			{
				windowSkillUpgrades->Draw(args);
			}

			i = 0;
			while (i < 4)
			{
				Skill* skill = sys->GetSkills()[i];
				GUIControl* cont = windowSkills->ChildControls()[i];

				args.SpriteBatch->Draw(
					skill->GetIconTexture(),
					cont->GetBoundingBox().Position() + Vector2(13.0f),
					0.0f,
					Vector2::Zero,
					0.35f,
					0.9f
				);

				args.SpriteBatch->DrawString(
					GUIControl::GetDefaultFont(),
					skill->GetCurrentLevelString(),
					cont->GetBoundingBox().Position() + Vector2(13.0f),
					Color::White,
					0.8f
				);

				i++;
			}
		}
		#pragma endregion

		#pragma region Member - Update
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

			SkillSystem* sys = gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys();

			if (sys->GetSkillUpgrades() > 0)
			{
				windowSkillUpgrades->Update(args);
			}
		}
		#pragma endregion
	}
}
