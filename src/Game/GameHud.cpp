
#include "Game/GameHud.h"
#include "Game/GameState.h"
#include "Game/SceneLevel.h"
#include "Game/SceneMenuMain.h"

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
			buttonMenu = TIKI_NEW GUIImage(engine);
			buttonMenu->SetTexture(engine->content->LoadTexture(L"hud/if_menu"));
			buttonMenu->SPosition() = Vector2(10.0f, 0.0f);
			buttonMenu->Click.AddHandler(this);
			enabledControls.Add(buttonMenu);

			windowData = TIKI_NEW GUIImage(engine);
			windowData->SetTexture(engine->content->LoadTexture(L"hud/if_data"));
			enabledControls.Add(windowData);

			windowMain = TIKI_NEW GUIImage(engine);
			windowMain->SetTexture(engine->content->LoadTexture(L"hud/if_main"));
			enabledControls.Add(windowMain);

			windowMinimap = TIKI_NEW GUIImage(engine);
			windowMinimap->SetTexture(engine->content->LoadTexture(L"hud/if_minimap"));
			enabledControls.Add(windowMinimap);
			
			imgMinimap = TIKI_NEW GUIImage(engine);
			imgMinimap->Click.AddHandler(this);
			enabledControls.Add(imgMinimap);

			labelRes = TIKI_NEW GUILabel(engine);
			labelRes->Text() = L"0";
			windowData->AddChild(labelRes);

			controlSkills = TIKI_NEW GUIControl(engine);
			controlSkills->SSize() = Vector2(295, 90);

			UInt32 i = 0;
			while (i < 4)
			{
				GUIImage* cmd = TIKI_NEW GUIImage(engine);
				cmd->SPosition() = Vector2(0.0f + (68.0f * i), 0.0f);
				cmd->Click.AddHandler(this);

				controlSkills->AddChild(cmd);

				i++;
			}
			windowMain->AddChild(controlSkills);

			controlSkillUpgrades = TIKI_NEW GUIWindow(engine);
			controlSkillUpgrades->SSize() = Vector2(219, 67);

			i = 0;
			while (i < 4)
			{
				GUIButton* cmd = TIKI_NEW GUIButton(engine);
				cmd->SSize() = Vector2(48, 48);
				cmd->SPosition() = Vector2(10.0f + (50.0f * i), 10.0f);
				cmd->Text() = L"+";
				cmd->Click.AddHandler(this);
				cmd->UserData = (void*)i;

				controlSkillUpgrades->AddChild(cmd);

				i++;
			}

			controlBuildSlot = TIKI_NEW GUIImage(engine);
			controlBuildSlot->SetTexture(engine->content->LoadTexture(L"hud/if_build"));
			controlBuildSlot->Click.AddHandler(this);

			texInfo = engine->content->LoadTexture(L"hud/unit_bg");
			texHealth = engine->content->LoadTexture(L"hud/unit_health");
			texShield = engine->content->LoadTexture(L"hud/unit_shield");

			texMinimapMop = engine->content->LoadTexture(L"hud/minimap_mop");
			texMinimapHero = engine->content->LoadTexture(L"hud/minimap_hero");

			texBarHpBg = engine->content->LoadTexture(L"hud/if_hp_bar");
			texBarHpText = engine->content->LoadTexture(L"hud/if_hp");

			texBarExpBg = engine->content->LoadTexture(L"hud/if_exp_bar");
			texBarExpText = engine->content->LoadTexture(L"hud/if_exp");

			gameState->UnitSelectionChanged.AddHandler(this);
			engine->graphics->ScreenSizeChanged.AddHandler(this);
		}

		GameHud::~GameHud()
		{
			SafeRelease(&buttonMenu);
			SafeRelease(&windowData);
			SafeRelease(&windowMain);
			SafeRelease(&windowMinimap);
			
			SafeRelease(&controlSkillUpgrades);
			SafeRelease(&controlBuildSlot);

			SafeRelease(&imgMinimap);

			SafeRelease(&texInfo);
			SafeRelease(&texHealth);
			SafeRelease(&texShield);
			SafeRelease(&texMinimapMop);
			SafeRelease(&texMinimapHero);

			SafeRelease(&texBarHpBg);
			SafeRelease(&texBarHpText);

			SafeRelease(&texBarExpBg);
			SafeRelease(&texBarExpText);
		}
		#pragma endregion

		#pragma region Init
		void GameHud::Init()
		{
			imgMinimap->SetTexture(engine->content->LoadTexture(
				L"terrain/minimap_" + StringAtoW(gameState->GetScene()->GLevel()->GetName())
			));

			SkillSystem* ss = gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys();

			for (UInt32 i = 0; i < ss->GetSkills().Count(); i++)
			{
				GUIImage* img = (GUIImage*)controlSkills->ChildControls()[ i ];

				img->SetTexture(
					ss->GetSkills()[ i ]->GetIconTexture()
				);
			}

			this->ResetScreen();
		}
		#pragma endregion

		#pragma region Member - ResetScreen
		void GameHud::ResetScreen()
		{
			vp = engine->graphics->GetViewPort()->GetSize();
			scale = vp.X / 1680.0f;
			
			buttonMenu->SSize() = buttonMenu->GetTexture()->GetSize() * scale;
			windowData->SSize() = windowData->GetTexture()->GetSize() * scale;
			windowMain->SSize() = windowMain->GetTexture()->GetSize() * scale;
			windowMinimap->SSize() = windowMinimap->GetTexture()->GetSize() * scale;

			windowData->SPosition() = Vector2(vp.X - windowData->GSize().X - 10.0f, 0.0f);
			windowMain->SPosition() = Vector2(0.0, vp.Y - windowMain->GSize().Y);
			windowMinimap->SPosition() = Vector2(vp.X - windowMinimap->GSize().X, vp.Y - windowMinimap->GSize().Y);

			imgMinimap->SPosition() = windowMinimap->GPosition() + (Vector2(22.0f) * scale);
			imgMinimap->SSize() = Vector2(270.0f) * scale;

			for (UInt32 i = 0; i < controlSkills->ChildControls().Count(); i++)
			{
				GUIImage* img = (GUIImage*)controlSkills->ChildControls()[ i ];

				if (img->GetTexture())
				{
					img->SSize() = img->GetTexture()->GetSize() * (78.0f / 128.0f) * scale;
					img->SPosition() = Vector2((344.0f * scale) + (90.0f * scale * (float)i), vp.Y - img->GSize().Y - (110.0f * scale));
				}
			}

			controlSkillUpgrades->SPosition() = Vector2(350.0f * scale, vp.Y - (290.0f * scale));

			controlBuildSlot->SPosition() = Vector2(964.0f * scale, vp.Y - (189.0f * scale));
			controlBuildSlot->SSize() = controlBuildSlot->GetTexture()->GetSize() * scale;

			labelRes->SPosition() = Vector2(vp.X - (168.0f * scale), 14.0f * scale);

			//windowSkills->SPosition() = Vector2(100, (float)vp->Height - 90);
			//windowBuildSlot->SPosition() = Vector2(100, (float)vp->Height - 90);

			//windowResources->SPosition() = Vector2((float)vp->Width - 200, -15.0f);
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

			if (selectedSlot)
			{
				controlBuildSlot->Draw(args);
			}

			#pragma region SkillSystem
			TikiBot* hero = gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>();
			SkillSystem* sys = hero->GetSkillSys();

			if (sys->GetSkillUpgrades() > 0)
			{
				controlSkillUpgrades->Draw(args);
			}

			i = 0;
			while (i < 4)
			{
				Skill* skill = sys->GetSkills()[i];
				GUIControl* cont = controlSkills->ChildControls()[ i ];

				args.SpriteBatch->Draw(
					skill->GetIconTexture(),
					cont->GetBoundingBox().Position(),
				 	0.0f,
					Vector2::Zero,
					(Vector2(80.0f) / 128.0f) * scale ,
					0.9f,
					Color::White,
					(skill->GetAtWorkState() ? -(float)args.Time.TotalTime : (float)skill->GetCooldownState())
				);

				args.SpriteBatch->DrawString(
					GUIControl::GetDefaultFont(),
					skill->GetCurrentLevelString(),
					cont->GetBoundingBox().Position() + cont->GSize() - Vector2(15.0f * scale, 20.0f * scale),
					Color::White,
					0.8f
				);

				i++;
			}
			#pragma endregion

			#pragma region Health/XP
			float hp = (float)(hero->Health() / hero->MaxHealth());
			float xp = (float)((sys->GetXP() - sys->GetXPLastLevel()) / (sys->GetXPNextLevel() - sys->GetXPLastLevel()));

			args.SpriteBatch->Draw(
				texBarHpBg,
				RectangleF::Create(
					344.0f * scale,
					vp.Y - (98.0f * scale),
					699.0f * scale * hp,
					32.0f * scale
				),
				texBarExpBg->GetRectangle(),
				Color::White,
				0.9f
			);

			args.SpriteBatch->Draw(
				texBarHpText,
				RectangleF::Create(
					355.0f * scale,
					vp.Y - (98.0f * scale),
					(float)texBarHpText->GetWidth() * scale,
					(float)texBarHpText->GetHeight() * scale
				),
				texBarHpText->GetRectangle(),
				Color::White,
				0.8f
			);

			args.SpriteBatch->Draw(
				texBarExpBg,
				RectangleF::Create(
					344.0f * scale,
					vp.Y - (52.0f * scale),
					699.0f * scale * xp,
					32.0f * scale
				),
				texBarExpBg->GetRectangle(),
				Color::White,
				0.9f
			);

			args.SpriteBatch->Draw(
				texBarExpText,
				RectangleF::Create(
					355.0f * scale,
					vp.Y - (52.0f * scale),
					(float)texBarExpText->GetWidth() * scale,
					(float)texBarExpText->GetHeight() * scale
				),
				texBarExpText->GetRectangle(),
				Color::White,
				0.8f
			);
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
				controlSkillUpgrades->Update(args);
			}

			if (selectedSlot)
			{
				controlBuildSlot->Update(args);
			}
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void GameHud::Handle(GameState* sender, const UnitSelectionChangedArgs& args)
		{
			selectedBot = 0;
			selectedSlot = 0;

			if (args.SelectedUnits.Count() != 0)
			{
				selectedBot = args.SelectedUnits[0]->GetComponent<TikiBot>();
			}
			else if (args.SelectedSlots.Count() != 0)
			{
				selectedSlot = args.SelectedSlots[0]->GetComponent<BuildSlot>();
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
				engine->SetSceneMenu();
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
			else if (sender->GetParent() == controlSkills)
			{
				Int32 index = controlSkills->ChildControls().IndexOf(sender);

				if (index != -1)
				{
					gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys()->GetSkills().Get(index)->Aktivate();
				}
			}
			else if (sender->GetParent() == controlSkillUpgrades)
			{
				UInt32 index = (UInt32)sender->UserData;

				SkillSystem* sys = gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys();
				sys->UpgradeSkill(index);

				Skill* skill = sys->GetSkills().Get(index);
				if (skill->GetCurrentLevel() == skill->GetDesc().MaxLevel)
				{
					controlSkillUpgrades->RemoveChild(sender);
				}
			}
			else if (sender == controlBuildSlot)
			{
				gameState->GetUnitSelection()->BuildCommand(selectedSlot);
			}
		}
		#pragma endregion
	}
}
