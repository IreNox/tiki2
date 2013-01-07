
#include "Game/PPFogOfWar.h"

#include "Core/IGraphics.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Game/SceneLevel.h"
#include "Game/TikiBot.h"
#include "Game/Weapon.h"
#include "Game/WeaponSystem.h"
#include "Game/SkillSystem.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		PPFogOfWar::PPFogOfWar(GameState* state)
			: PostProcess(state->GetEngine()), state(state)
		{
			SafeAddRef(
				engine->content->LoadShader(L"pp_fow"),
				&shader
			);

			buffer = engine->graphics->CreateConstantBuffer(sizeof(CBFogOfWar));
			shader->SetConstantBuffer("FogOfWar", buffer);

			PostProcessPass* pass = new PostProcessPass(engine, shader);
			pass->AddInput("rtScreen", 0);
			pass->AddInput("rtDepth", engine->graphics->GetDepthTarget());
			pass->AddOutput(0, 0);
			this->AddPass(pass);		

			state->UnitSelectionChanged.AddHandler(this);
		}

		PPFogOfWar::~PPFogOfWar()
		{
			SafeRelease(&buffer);
			SafeRelease(&shader);
		}
		#pragma endregion

		#pragma region Member - Update
		void PPFogOfWar::UpdatePass(UInt32 index, const DrawArgs& args)
		{
			IRenderTarget* input;
			IRenderTarget* output;
			engine->graphics->SwitchScreenTarget(&input, &output);

			passes[0]->SetInput("rtScreen", input);
			passes[0]->SetOutput(0, output);

#if _DEBUG
			shader->SetConstantBuffer("FogOfWar", buffer);
#endif

			CBFogOfWar* fow = buffer->MapT<CBFogOfWar>();

#if TIKI_USE_SCENEGRAPH
			UInt32 count = 0;
			state->GetScene()->SceneGraph.Do([&](GameObject* go)
			{
				TikiBot* bot = go->GetComponent<TikiBot>();

				if (bot != 0 && bot->GetFaction() == 0)
				{
					fow->Units[count].Position = bot->Pos();
					fow->Units[count].Range = bot->GetSightRadius();
					fow->Units[count].Type = (selected.Contains(bot->GetGameObject()) ? 1.0f : 0.0f);
					count++;

					if (bot->GetSkillSys() != 0)
					{
						List<Skill*>& skills = bot->GetSkillSys()->GetSkills();

						UInt32 i = 0;
						while (i < skills.Count())
						{
							if (skills[i]->GetOnActivation() && skills[i]->GetHasAOE())
							{
								shader->SetTexture("SkillCrosshair", skills[i]->GetCrosshairTexture());

								fow->Units[count].Position = args.Update.Input.MousePosition;
								fow->Units[count].Range = skills[i]->GetDesc().AOERange;
								fow->Units[count].Type = (skills[i]->GetInRange() ? 3.0f : 4.0f );
								count++;
							}

							i++;
						}
					}
				}

			});
#else
			UInt32 i = 0;
			UInt32 count = 0;
			while (i < state->GetScene()->GetElements().Count() && count < 32)
			{
				TikiBot* bot = state->GetScene()->GetElements()[i]->GetComponent<TikiBot>();

				if (bot != 0 && bot->GetFaction() == 0)
				{
					fow->Units[count].Position = bot->Pos();
					fow->Units[count].Range = bot->GetSightRadius();
					fow->Units[count].Type = (selected.Contains(bot->GetGameObject()) ? 1.0f : 0.0f);
					count++;

					if (bot->GetSkillSys() != 0)
					{
						List<Skill*>& skills = bot->GetSkillSys()->GetSkills();

						UInt32 i = 0;
						while (i < skills.Count())
						{
							if (skills[i]->GetOnActivation() && skills[i]->GetHasAOE())
							{
								shader->SetTexture("SkillCrosshair", skills[i]->GetCrosshairTexture());

								fow->Units[count].Position = args.Update.Input.MousePosition;
								fow->Units[count].Range = skills[i]->GetDesc().AOERange;
								fow->Units[count].Type = (skills[i]->GetInRange() ? 3.0f : 4.0f );
								count++;
							}

							i++;
						}
					}
				}

				i++;
			}
#endif

			float size = (float)state->GetScene()->GLevel()->GetTerrain()->GSize();

			fow->UnitsCount = (float)count;
			fow->MapSize = Vector3(size, state->GetScene()->GLevel()->GetTerrain()->GElevation(), size);

			buffer->Unmap();
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void PPFogOfWar::Handle(GameState* sender, const UnitSelectionChangedArgs& args)
		{
			selected.Clear();

			UInt32 i = 0;
			while (i < args.SelectedUnits->Count())
			{
				selected.Add(args.SelectedUnits->Get(i));
				i++;
			}
		}
		#pragma endregion

	}
}