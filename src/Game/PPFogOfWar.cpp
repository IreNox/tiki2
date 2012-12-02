
#include "Game/PPFogOfWar.h"

#include "Core/IGraphics.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Game/SceneLevel.h"
#include "Game/TikiBot.h"
#include "Game/Weapon.h"
#include "Game/WeaponSystem.h"

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

			UInt32 i = 0;
			UInt32 count = 0;
			while (i < state->GetScene()->GetElements().Count())
			{
				TikiBot* bot = state->GetScene()->GetElements()[i]->GetComponent<TikiBot>();

				if (bot != 0 && bot->GetFaction() == 0)
				{
					fow->Units[count].Position = bot->Pos();
					fow->Units[count].Range = bot->GetWeaponSys()->GetCurrentWeapon()->GetIdealRange();
					fow->Units[count].Type = (selected.Contains(bot->GetGameObject()) ? 1.0f : 0.0f);

					count++;
				}

				i++;
			}

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