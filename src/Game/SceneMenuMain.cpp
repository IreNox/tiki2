
#include "Game/SceneMenuMain.h"

#include "Core/IGraphics.h"

#include "Game/SceneTim.h"
#include "Game/SceneMark.h"
#include "Game/SceneAdrian.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		SceneMenuMain::SceneMenuMain(Engine* engine)
			: Scene(engine)
		{
		}

		SceneMenuMain::~SceneMenuMain()
		{
			SafeRelease(&image);
			SafeRelease(&window);
		}
		#pragma endregion

		#pragma region Member - Init
		void SceneMenuMain::Initialize(const InitializationArgs& args)
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			GameObject* obj = new CameraObject(engine);
			this->AddElement(obj);

			ITexture* logo = engine->content->LoadTexture(L"logo");

			image = new GUIImage(engine);
			image->SetTexture(logo);
			image->SSize() = Vector2(200);
			image->AddRef();

			window = new GUIWindow(engine);
			window->SSize() = Vector2(350, 400);
			window->AddRef();

			wcstring text[] = {
				L"Start Game",
				L"Test Scene - Tim",
				L"Test Scene - Mark",
				L"Test Scene - Adrian",
				L"Exit",
			};

			UInt32 i = 0;
			while (i < 5)
			{
				GUIButton* cmd = new GUIButton(engine);
				cmd->SSize() = Vector2(300, 50);
				cmd->Text() = text[i];
				cmd->UserData = (void*)i;
				cmd->Click.AddHandler(this);

				window->AddChild(cmd);

				i++;
			}

			this->Handle(engine->graphics, ScreenSizeChangedArgs(engine->graphics, engine->graphics->GetViewPort()));
			engine->graphics->ScreenSizeChanged.AddHandler(this);

			Scene::Initialize(args);
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void SceneMenuMain::Draw(const DrawArgs& args)
		{
			image->Draw(args);
			window->Draw(args);

			Scene::Draw(args);
		}

		void SceneMenuMain::Update(const UpdateArgs& args)
		{
			image->Update(args);
			window->Update(args);

			Scene::Update(args);
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void SceneMenuMain::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			image->SPosition() = Vector2(
				((float)args.CurrentViewPort->Width / 2) - 100,
				25.0f
			);

			window->SPosition() = Vector2(
				((float)args.CurrentViewPort->Width / 2) - 175,
				250.0f
			);

			UInt32 i = 0;
			while (i < window->ChildControls().Count())
			{
				window->ChildControls()[i]->SPosition() = Vector2(
					25,
					25.0f + (i * 75)
				);
				i++;
			}
		}

		void SceneMenuMain::Handle(GUIControl* sender, const ClickEventArgs& args)
		{
			Scene* s = 0;
			SceneLevel* sLevel = 0;

			switch ((Int32)sender->UserData)
			{
			case 0:
				sLevel = new SceneLevel(engine);
				engine->SetScene(sLevel);
				sLevel->LoadLevel(1);
				break;
			case 1:
				s = new SceneTim(engine);
				engine->SetScene(s);
				break;
			case 2:
				s = new SceneMark(engine);
				engine->SetScene(s);
				break;
			case 3:
				s = new SceneAdrian(engine);
				engine->SetScene(s);
				break;
			case 4:
				engine->Exit();
				break;
			}
		}
		#pragma endregion

	}
}