
#include "Game/GameHud.h"
#include "Game/GameState.h"
#include "Game/SceneLevel.h"

#include "Game/TikiBot.h"
#include "Game/PlayerBase.h"
#include "Game/SkillSystem.h"
#include "Game/UnitSelection.h"

#include "Core/IPhysics.h"
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
			: EngineObject(state->GetEngine()), gameState(state), selectedBot(0), selectedSlot(0)
		{
			buttonMenu = TIKI_NEW GUIButton(engine);
			buttonMenu->SPosition() = Vector2(20, -15);
			buttonMenu->Text() = L"Menu";
			buttonMenu->SSize() = Vector2(100, 55);
			buttonMenu->AddRef();
			buttonMenu->Click.AddHandler(this);
			enabledControls.Add(buttonMenu);

			windowResources = TIKI_NEW GUIWindow(engine);
			windowResources->SSize() = Vector2(180, 55);
			windowResources->AddRef();
			enabledControls.Add(windowResources);

			imgMinimap = TIKI_NEW GUIImage(engine);
			imgMinimap->Click.AddHandler(this);
			enabledControls.Add(imgMinimap);

			GUIImage* image = TIKI_NEW GUIImage(engine);
			image->SetTexture(engine->content->LoadTexture(L"hud/mass"));
			image->SSize() = Vector2(16, 16);
			image->SPosition() = Vector2(16, 20);
			windowResources->AddChild(image);

			labelRes = TIKI_NEW GUILabel(engine);
			labelRes->Text() = L"0";
			labelRes->SPosition() = Vector2(35, 20);
			windowResources->AddChild(labelRes);

			windowSkills = TIKI_NEW GUIWindow(engine);
			windowSkills->SSize() = Vector2(295, 90);

			UInt32 i = 0;
			while (i < 4)
			{
				GUIButton* cmd = TIKI_NEW GUIButton(engine);
				cmd->SSize() = Vector2(70, 70);
				cmd->SPosition() = Vector2(10.0f + (68.0f * i), 10.0f);
				cmd->Click.AddHandler(this);

				windowSkills->AddChild(cmd);

				i++;
			}

			windowSkillUpgrades = TIKI_NEW GUIWindow(engine);
			windowSkillUpgrades->SSize() = Vector2(219, 67);

			i = 0;
			while (i < 4)
			{
				GUIButton* cmd = TIKI_NEW GUIButton(engine);
				cmd->SSize() = Vector2(48, 48);
				cmd->SPosition() = Vector2(10.0f + (50.0f * i), 10.0f);
				cmd->Text() = L"+";
				cmd->Click.AddHandler(this);
				cmd->UserData = (void*)i;

				windowSkillUpgrades->AddChild(cmd);

				i++;
			}

			windowBuildSlot = TIKI_NEW GUIWindow(engine);
			windowBuildSlot->SSize() = Vector2(90, 90);

			GUIButton* cmd = TIKI_NEW GUIButton(engine);
			cmd->SSize() = Vector2(70, 70);
			cmd->SPosition() = Vector2(10.0f, 10.0f);
			cmd->Text() = L"Build";
			cmd->Click.AddHandler(this);

			windowBuildSlot->AddChild(cmd);

			texInfo = engine->content->LoadTexture(L"hud/unit_bg");
			texHealth = engine->content->LoadTexture(L"hud/unit_health");
			texShield = engine->content->LoadTexture(L"hud/unit_shield");

			texMinimapMop = engine->content->LoadTexture(L"hud/minimap_mop");
			texMinimapHero = engine->content->LoadTexture(L"hud/minimap_hero");
			
			gameState->UnitSelectionChanged.AddHandler(this);
			engine->graphics->ScreenSizeChanged.AddHandler(this);

			this->ResetScreen();
		}

		GameHud::~GameHud()
		{
			SafeRelease(&buttonMenu);

			SafeRelease(&windowSkills);
			SafeRelease(&windowSkillUpgrades);
			SafeRelease(&windowBuildSlot);

			SafeRelease(&windowResources);

			SafeRelease(&imgMinimap);

			SafeRelease(&texInfo);
			SafeRelease(&texHealth);
			SafeRelease(&texShield);
			SafeRelease(&texMinimapMop);
			SafeRelease(&texMinimapHero);
		}
		#pragma endregion

		#pragma region Init
		void GameHud::Init()
		{
			imgMinimap->SetTexture(engine->content->LoadTexture(
				L"terrain/minimap_" + StringAtoW(gameState->GetScene()->GLevel()->GetName())
			));
			imgMinimap->SSize() = Vector2(196, 196);
		}
		#pragma endregion

		#pragma region Member - ResetScreen
		void GameHud::ResetScreen()
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			imgMinimap->SPosition() = Vector2((float)vp->Width - 200, (float)vp->Height - 200);

			windowSkills->SPosition() = Vector2(100, (float)vp->Height - 90);
			windowSkillUpgrades->SPosition() = Vector2(140, (float)vp->Height - 150);
			windowBuildSlot->SPosition() = Vector2(100, (float)vp->Height - 90);

			windowResources->SPosition() = Vector2((float)vp->Width - 200, -15.0f);
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

			#pragma region SkillSystem
			if (selectedBot != 0 && selectedBot->EntityType() == ET_Hero)
			{
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
						Vector2(0.35f),
						0.9f,
						Color::White,
						(skill->GetAtWorkState() ? -(float)args.Time.TotalTime : (float)skill->GetCooldownState())
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

			#pragma region Minimap/Healthbars
			Matrix vp = args.CurrentCamera->WorldToScreen();
			Vector2 ss = args.Graphics->GetViewPort()->GetSize();

			Vector2 mmCenter = imgMinimap->GPosition() + (imgMinimap->GSize() / 2);
			float levelSize = gameState->GetScene()->GLevel()->GetTerrain()->GSize() * 0.75f;

			Vector2 screenPoints[] = {
				Vector2(0, 0),
				Vector2(ss.X, 0),
				Vector2(ss.X, ss.Y),
				Vector2(0, ss.Y)
			};

			List<Vector2> frustum;

			i = 0;
			while (i < 4)
			{
				Ray ray = gameState->GetScene()->GetMainCamera()->ScreenPointToRay(screenPoints[i]);
				RaycastHit hit;
				Vector2 point = Vector2::Zero;

				if (engine->physics->RayCast(ray, &hit))
				{
					point = hit.Point.XZ();
				}

				point /= levelSize;
				point *= imgMinimap->GSize().X;
				point += mmCenter;

				frustum.Add(point);
				
				i++;
			}

			args.SpriteBatch->DrawLine(frustum, Color::White, 0.8f, true);


#if TIKI_CULLING

			UINT gameObjectCount = gameState->GetScene()->GetHudContent().Count();

			for(UINT i = 0; i < gameObjectCount; i++)
			{
				GameObject* go = gameState->GetScene()->GetHudContent()[i];

#else
			UINT gameObjectCount = gameState->GetScene()->GetDrawContent().Count();

			for(UINT i = 0; i < gameObjectCount; i++)
			{
				GameObject* go = gameState->GetScene()->GetDrawContent()[i];
#endif
				TikiBot* bot = go->GetComponent<TikiBot>();

				if (bot != 0)
				{
					Vector3 pos = go->PRS.GPosition();					
					pos.Y += bot->GetController()->GetHeight() + 1.0f;

					if (gameState->GetScene()->GetMainCamera()->GetFrustum().PointInFrustum(pos))
					{
						pos = Matrix::TransformCoordinate(pos, vp) + Vector3(1, 1, 0);
						pos *= 0.5f;
						pos = Vector3(pos.X * ss.X, (1 - pos.Y) * ss.Y, 0);

						if (bot->EntityType() == ET_Hero)
						{
							args.SpriteBatch->Draw(
								texInfo,
								RectangleF::Create(pos.X - 40, pos.Y - 20, 80, 16),
								Color::White,
								1.2f
							);

							args.SpriteBatch->Draw(
								texHealth,
								RectangleF::Create(pos.X - 39, pos.Y - 19, (float)(bot->Health() / bot->MaxHealth()) * 78.0f, 11),
								Color::White,
								1.1f
							);

							float xp = (float)((bot->GetSkillSys()->GetXP() - bot->GetSkillSys()->GetXPLastLevel()) / (bot->GetSkillSys()->GetXPNextLevel() - bot->GetSkillSys()->GetXPLastLevel()));
							args.SpriteBatch->Draw(
								texShield,
								RectangleF::Create(pos.X - 39, pos.Y - 8, xp * 78.0f, 4),
								Color::White,
								1.1f
							);
						}
						else
						{
							args.SpriteBatch->Draw(
								texInfo,
								RectangleF::Create(pos.X - 20, pos.Y - 16, 40, 9),
								Color::White,
								1.2f
							);

							args.SpriteBatch->Draw(
								texHealth,
								RectangleF::Create(pos.X - 19, pos.Y - 15, (float)(bot->Health() / bot->MaxHealth()) * 38.0f, 7),
								Color::White,
								1.1f
							);
						}
					}

					ITexture* tex = (bot->EntityType() == ET_Hero ? texMinimapHero : texMinimapMop);

					args.SpriteBatch->Draw(
						tex,
						mmCenter + ((go->PRS.GPosition().XZ() / levelSize) * imgMinimap->GSize().X),
						0.0f,
						tex->GetCenter(),
						1.0f,
						0.8f,
						(bot->GetFaction() == 0 ? Color::Green : Color::Red)
					);
				}
			}
			#pragma endregion
		}
		#pragma endregion

		#pragma region Member - Update
		void GameHud::Update(const UpdateArgs& args)
		{
			wstring res = StringConvert::ToWString(gameState->GetResource());
			labelRes->Text() = res.Substring(0, res.IndexOf(L'.'));

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

		#pragma region Member - EventHandler
		void GameHud::Handle(GameState* sender, const UnitSelectionChangedArgs& args)
		{
			selectedBot = 0;
			selectedSlot = 0;

			enabledControls.Remove(windowSkills);
			enabledControls.Remove(windowBuildSlot);

			if (args.SelectedUnits.Count() != 0)
			{
				selectedBot = args.SelectedUnits[0]->GetComponent<TikiBot>();
			}
			else if (args.SelectedSlots.Count() != 0)
			{
				selectedSlot = args.SelectedSlots[0]->GetComponent<BuildSlot>();
			}

			if (selectedBot != 0 && selectedBot->EntityType() == ET_Hero)
			{
				enabledControls.Add(windowSkills);
			}
			else if (selectedSlot != 0)
			{
				enabledControls.Add(windowBuildSlot);
			}
		}

		void GameHud::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			this->ResetScreen();
		}
		#pragma endregion

		#pragma region Member - EventHandler - Click
		void GameHud::Handle(GUIControl* sender, const ClickEventArgs& args)
		{
			if (sender == buttonMenu)
			{
				//engine->SetScene()
			}
			else if (sender == imgMinimap)
			{
				Vector2 clickPos = args.ClickPosition;
				clickPos -= imgMinimap->GPosition() + (imgMinimap->GSize() / 2);
				clickPos /= imgMinimap->GSize().X;
				clickPos *= gameState->GetScene()->GLevel()->GetTerrain()->GSize() * 0.75f;

				if (args.Button == MB_Left)
				{
					Vector3& pos = gameState->GetScene()->GetMainCamera()->GetGameObject()->PRS.SPosition();
					pos.X = clickPos.X;
					pos.Z = clickPos.Y;
				}
				else if (args.Button == MB_Right)
				{
					Vector3 pos = Vector3(
						clickPos.X,
						0,
						clickPos.Y
					);
					pos.Y = gameState->GetScene()->GLevel()->GetTerrain()->SampleHeight(pos);

					gameState->GetUnitSelection()->MoveCommand(0, pos, false, false);
				}
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
				UInt32 index = (UInt32)sender->UserData;

				SkillSystem* sys = gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys();
				sys->UpgradeSkill(index);

				Skill* skill = sys->GetSkills().Get(index);
				if (skill->GetCurrentLevel() == skill->GetDesc().MaxLevel)
				{
					windowSkillUpgrades->RemoveChild(sender);
				}
			}
			else if (sender->GetParent() == windowBuildSlot)
			{
				gameState->GetUnitSelection()->BuildCommand(selectedSlot);
			}
		}
		#pragma endregion

		#pragma region Private Member - Init
		#pragma endregion
	}
}
