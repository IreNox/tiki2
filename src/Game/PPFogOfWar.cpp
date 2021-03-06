
#include "Game/PPFogOfWar.h"

#include "Core/IGraphics.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Game/SceneLevel.h"
#include "Game/TikiBot.h"
#include "Game/BuildSlot.h"
#include "Game/Weapon.h"
#include "Game/WeaponSystem.h"
#include "Game/SkillSystem.h"

#include "Game/PlayerBase.h"

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
			shader->SetBoolean("heroDead", false);

			PostProcessPass* pass = TIKI_NEW PostProcessPass(engine, shader);
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

			PlayerBase* pb = 0;
			pb = state->GetPart<PlayerBase>(0);
			if (pb != 0)
			{
				shader->SetBoolean("heroDead", pb->IsHeroDead());
			}

			CBFogOfWar* fow = buffer->MapT<CBFogOfWar>();

			UInt32 i = 0;
			UInt32 count = 0;
			List<GameObject*> gos;
			state->GetScene()->SceneGraph.Find(gos);

			while (i <gos.Count() && count < FOW_CBSIZE)
			{
				TikiBot* bot = gos[i]->GetComponent<TikiBot>();

				if (bot != 0 && bot->GetFaction() == 0)
				{
					fow->Units[count].Position = bot->Pos();
					fow->Units[count].Range = (float)bot->GetAttSys()[TA_SightRadius] / 2.0f;
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
								fow->Units[count].Type = 3.0f; //(skills[i]->GetInRange() ? 3.0f : 4.0f );
								count++;
							}

							i++;
						}
					}
				}

				i++;
			}

			i = 0;
			while (i < selected.Count() && count < FOW_CBSIZE)
			{
				BuildSlot* slot = selected[i]->GetComponent<BuildSlot>();

				if (slot != 0)
				{
					fow->Units[count].Position = selected[i]->PRS.GPosition().XZ();
					fow->Units[count].Range = 0;
					fow->Units[count].Type = 1.0f;
					count++;
				}

				i++;
			}

			float size = (float)state->GetScene()->GLevel()->GetTerrain()->GSize();

			fow->UnitsCount = (float)count;
			fow->MapSize = Vector3(size, state->GetScene()->GLevel()->GetTerrain()->GElevation(), size);

			buffer->Unmap();

			shader->SetConstantBuffer( "FogOfWar", buffer );
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void PPFogOfWar::Handle(GameState* sender, const UnitSelectionChangedArgs& args)
		{
			selected.Clear();
			selected.AddRange(args.SelectedUnits);
			selected.AddRange(args.SelectedSlots);
		}
		#pragma endregion

	}
}