
#include "Game/SceneMenuMain.h"

#include "Core/IGraphics.h"

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
		}
		#pragma endregion

		#pragma region Member - Init
		void SceneMenuMain::Initialize(const InitializationArgs& args)
		{
			ViewPort* vp = engine->graphics->GetViewPort();

			this->AddElement(new CameraObject(engine));

			ITexture* logo = engine->content->LoadTexture(L"logo");

			GUIImage* img = new GUIImage(engine);
			img->SetTexture(logo);
			img->Position() = Vector2(
				((float)vp->Width / 2) - 100,
				25.0f
			);
			img->Size() = Vector2(200);
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
				cmd->Position() = Vector2(
					((float)vp->Width / 2) - 150,
					250.0f + (i * 75)
				);
				cmd->Size() = Vector2(300, 50);
				cmd->Text() = text[i];

				buttons.Add(cmd);
				controls.Add(cmd);

				i++;
			}

			engine->graphics->ScreenSizeChanged.AddHandler(this);

			Scene::Initialize(args);
		}

		void SceneMenuMain::Handle(IGraphics* sender, const ScreenSizeChangedArgs& args)
		{
			UInt32 i = 0;
			while (i < controls.Count())
			{
				controls[i]->Position() = Vector2(
					(args.CurrentViewPort->Width / 2) - (controls[i]->Size().X / 2),
					controls[i]->Position().Y
				);
				i++;
			}
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
					switch (i)
					{
					case 0:
						engine->SetScene(sceneLevel);
						sceneLevel->LoadLevel(1);
						break;
					case 1:
					case 2:
					case 3:
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

	}
}