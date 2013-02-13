
#include "Game/SceneMenuMain.h"

#include "Core/IGraphics.h"
#include "Core/ISoundSystem.h"

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

			SafeRelease(&texBG);
		}
		#pragma endregion

		#pragma region Member - Init
		void SceneMenuMain::Initialize(const InitializationArgs& args)
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			GameObject* obj = TIKI_NEW CameraObject(engine);
			this->AddElement(obj);

			ITexture* logo = engine->content->LoadTexture(L"logo");

			texBG = engine->content->LoadTexture(L"hud/mainmenu_bg");
			
			image = TIKI_NEW GUIImage(engine);
			image->SetTexture(logo);
			image->AddRef();

			window = TIKI_NEW GUIWindow(engine);
			window->SSize() = Vector2(350, 475);
			window->AddRef();

			wcstring text[] = {
				L"Start - Level 1",
				L"Start - Level 2",
				L"Test Scene - Tim",
				L"Test Scene - Mark",
				L"Test Scene - Adrian",
				L"Exit",
			};

			UInt32 i = 0;
			while (i < 6)
			{
				GUIButton* cmd = TIKI_NEW GUIButton(engine);
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


			args.SpriteBatch->Draw(
				texBG,
				rectBG,
				texBG->GetRectangle(),
				Color::White,
				1.5f
			);

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
				((float)args.CurrentViewPort->Width / 2) - 384,
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

			float scale = TIKI_MAX(
				(float)args.Graphics->GetViewPort()->Width / (float)texBG->GetWidth(),
				(float)args.Graphics->GetViewPort()->Height / (float)texBG->GetHeight()
			)

			rectBG = RectangleF::Create(
				0,
				args.Graphics->GetViewPort()->Height - (texBG->GetHeight() * scale),
				texBG->GetWidth() * scale,
				texBG->GetHeight() * scale
			);
		}

		void SceneMenuMain::Handle(GUIControl* sender, const ClickEventArgs& args)
		{
			Scene* s = 0;
			SceneLevel* sLevel = 0;

			switch ((Int32)sender->UserData)
			{
			case 0:
				engine->sound->Play(
					engine->content->LoadSound(L"Mech_Spawn")
				);

				sLevel = TIKI_NEW SceneLevel(engine);
				engine->SetScene(sLevel);
				sLevel->LoadLevel(1);
				break;
			case 1:
				sLevel = TIKI_NEW SceneLevel(engine);
				engine->SetScene(sLevel);
				sLevel->LoadLevel(2);
				break;
			case 2:
				s = TIKI_NEW SceneTim(engine);
				engine->SetScene(s);
				break;
			case 3:
				s = TIKI_NEW SceneMark(engine);
				engine->SetScene(s);
				break;
			case 4:
				s = TIKI_NEW SceneAdrian(engine);
				engine->SetScene(s);
				break;
			case 5:
				engine->Exit();
				break;
			}
		}
		#pragma endregion

	}
}