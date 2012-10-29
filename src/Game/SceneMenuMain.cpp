
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
			: Scene(engine), sceneLevel(new SceneLevel(engine))
		{
		}

		SceneMenuMain::~SceneMenuMain()
		{
			SafeRelease(&sceneLevel);

			UInt32 i = 0;
			while (i < controls.Count())
			{
				SafeRelease(&controls[i]);
				i++;
			}
		}
		#pragma endregion

		#pragma region Member - Init
		void SceneMenuMain::Initialize(const InitializationArgs& args)
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			GameObject* obj = new CameraObject(engine);
			this->AddElement(obj);
			obj->Release();

			ITexture* logo = engine->content->LoadTexture(L"logo");

			GUIImage* img = new GUIImage(engine);
			img->SetTexture(logo);
			img->SPosition() = Vector2(
				((float)vp->Width / 2) - 100,
				25.0f
			);
			img->SSize() = Vector2(200);
			controls.Add(img);

			logo->Release();

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
				cmd->SPosition() = Vector2(
					((float)vp->Width / 2) - 150,
					250.0f + (i * 75)
				);
				cmd->SSize() = Vector2(300, 50);
				cmd->Text() = text[i];

				buttons.Add(cmd);
				controls.Add(cmd);

				i++;
			}

			engine->graphics->ScreenSizeChanged.AddHandler(this);

			Scene::Initialize(args);
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void SceneMenuMain::Draw(const DrawArgs& args)
		{
			UInt32 i = 0;
			while (i < controls.Count())
			{
				controls[i]->Draw(args);
				i++;
			}

			Scene::Draw(args);
		}

		void SceneMenuMain::Update(const UpdateArgs& args)
		{
			UInt32 i = 0;
			while (i < controls.Count())
			{
				controls[i]->Update(args);
				i++;
			}

			i = 0;
			while (i < buttons.Count())
			{
				if (buttons[i]->Clicked())
				{
					Scene* s = 0;

					switch (i)
					{
					case 0:
						engine->SetScene(sceneLevel);
						sceneLevel->LoadLevel(1);
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

				i++;
			}

			Scene::Update(args);
		}
		#pragma endregion

		#pragma region Member - EventHandler
		void SceneMenuMain::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			UInt32 i = 0;
			while (i < controls.Count())
			{
				controls[i]->SPosition() = Vector2(
					(args.CurrentViewPort->Width / 2) - (controls[i]->GSize().X / 2),
					controls[i]->GPosition().Y
					);
				i++;
			}
		}

		void SceneMenuMain::Handle(GUIControl* sender, const ClickEventArgs& args)
		{

		}
		#pragma endregion

	}
}