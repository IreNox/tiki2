
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
			//buttonMenu
			IFont* font = engine->librarys->CreateResource<IFont>();
			font->Create(L"Arial", 12);
			GUIControl::SetDefaultFont(font);

			texRes1 = engine->content->LoadTexture(L"hud/mass");
			texRes1->AddRef();
			imageRes1 = new GUIImage(state->GetEngine());
			imageRes1->SetTexture(texRes1);
			imageRes1->SSize() = Vector2(16, 16);
			enabledControls.Add(imageRes1);

			labelRes1 = new GUILabel(state->GetEngine());
			labelRes1->Text() = L"100/2500";
			enabledControls.Add(labelRes1);

			texRes2 = engine->content->LoadTexture(L"hud/energy");
			texRes2->AddRef();
			imageRes2 = new GUIImage(state->GetEngine());
			imageRes2->SetTexture(texRes2);
			imageRes2->SSize() = Vector2(16, 16);
			enabledControls.Add(imageRes2);

			labelRes2 = new GUILabel(state->GetEngine());
			labelRes2->Text() = L"5/10";
			enabledControls.Add(labelRes2);

			engine->graphics->ScreenSizeChanged.AddHandler(this);
			this->ResetScreen();
		}

		GameHud::~GameHud()
		{
			//SafeRelease(&buttonMenu);

			SafeRelease(&texRes1);
			SafeRelease(&imageRes1);
			SafeRelease(&labelRes1);

			SafeRelease(&texRes2);
			SafeRelease(&imageRes2);
			SafeRelease(&labelRes2);

			GUIControl::GetDefaultFont()->Release();
		}
		#pragma endregion

		#pragma region Member - ResetScreen
		void GameHud::ResetScreen()
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			imageRes1->SPosition() = Vector2((float)vp->Width - 200, 10);
			labelRes1->SPosition() = Vector2((float)vp->Width - 180, 10);

			imageRes2->SPosition() = Vector2((float)vp->Width - 100, 10);
			labelRes2->SPosition() = Vector2((float)vp->Width - 80, 10);
		}

		void GameHud::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			this->ResetScreen();
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
			wostringstream str;
			str << state->GetResource1() << L"/" << 1000;
			labelRes1->Text() = str.str();

			str = wostringstream();
			str << state->GetResource2() << L"/" << 100;
			labelRes2->Text() = str.str();

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
