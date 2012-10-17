
#include "Game/GameHud.h"
#include "Game/GameState.h"

#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		GameHud::GameHud(GameState* state)
			: EngineObject(state->GetEngine()), state(state)
		{
			//buttonMenu

			texRes1 = engine->content->LoadTexture(L"hud/mass");
			imageRes1 = new GUIImage(state->GetEngine());
			imageRes1->SetTexture(texRes1);
			imageRes1->Size() = Vector2(16, 16);
			enabledControls.Add(imageRes1);

			labelRes1 = new GUILabel(state->GetEngine());
			labelRes1->Text() = L"100/2500";
			enabledControls.Add(labelRes1);

			texRes2 = engine->content->LoadTexture(L"hud/energy");
			imageRes2 = new GUIImage(state->GetEngine());
			imageRes2->SetTexture(texRes2);
			imageRes2->Size() = Vector2(16, 16);
			enabledControls.Add(imageRes2);

			labelRes2 = new GUILabel(state->GetEngine());
			labelRes2->Text() = L"5/10";
			enabledControls.Add(labelRes2);

			this->ResetScreen();
		}

		GameHud::~GameHud()
		{
			SafeRelease(&buttonMenu);

			SafeRelease(&texRes1);
			SafeRelease(&imageRes1);
			SafeRelease(&labelRes1);

			SafeRelease(&texRes2);
			SafeRelease(&imageRes2);
			SafeRelease(&labelRes2);
		}
		#pragma endregion

		#pragma region Member - ResetScreen
		void GameHud::ResetScreen()
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			imageRes1->Position() = Vector2((float)vp->Width - 200, 10);
			labelRes1->Position() = Vector2((float)vp->Width - 220, 10);

			imageRes2->Position() = Vector2((float)vp->Width - 100, 10);
			labelRes2->Position() = Vector2((float)vp->Width - 120, 10);
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
