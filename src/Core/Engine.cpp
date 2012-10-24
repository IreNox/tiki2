
#include <math.h>
#include <string>
#include <sstream>

#include "Core/Engine.h"

#include "Core/Window.h"
#include "Core/LibraryManager.h"

#include "Core/Scene.h"

#include "Core/IInput.h"
#include "Core/IPhysics.h"
#include "Core/IGraphics.h"
#include "Core/ISoundSystem.h"
#include "Core/ISpriteBatch.h"

#include "Core/GameTime.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	#pragma region Class
	Engine::Engine()
		: scene(0), loadedModules(), input(0), sound(0), physics(0), graphics(0), sprites(0), content(0)
	{
	}

	Engine::~Engine()
	{
	}
	#pragma endregion

	#pragma region Member
	EngineDescription& Engine::GetEngineDescription()
	{
		return desc;
	}
	#pragma endregion

	#pragma region Member - Init
	bool Engine::Initialize(EngineDescription& desc)
	{
		this->desc = desc;

		window = new Window(this);		
		if (!initModule(window))
		{
			MessageBox(window->GetHWND(), L"Can't create Window.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		librarys = new LibraryManager(this);		
		if (!initModule(librarys))
		{
			MessageBox(window->GetHWND(), L"Can't create LibraryManager.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		content = librarys->CreateModule<IContentManager>();
		if (!initModule(content))
		{
			MessageBox(window->GetHWND(), L"Can't init ContentManager.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		graphics = librarys->CreateModule<IGraphics>();
		if (!initModule(graphics))
		{
			MessageBox(window->GetHWND(), L"Can't init Direct3D.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		sprites = librarys->CreateModule<ISpriteBatch>();
		if (!initModule(sprites))
		{
			MessageBox(window->GetHWND(), L"Can't init SpriteBatch.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		input = librarys->CreateModule<IInput>();
		if (!initModule(input))
		{
			MessageBox(window->GetHWND(), L"Can't init Input.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		sound = librarys->CreateModule<ISoundSystem>();
		if (!initModule(sound))
		{
			MessageBox(window->GetHWND(), L"Can't init Sound.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		physics = librarys->CreateModule<IPhysics>();
		if (!initModule(physics))
		{
			MessageBox(window->GetHWND(), L"Can't init Physics.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		return true;
	}
	#pragma endregion

	#pragma region Member - Dispose
	void Engine::Dispose()
	{
		SafeRelease(&scene);

		loadedModules.Remove(librarys);

		int i = loadedModules.Count() - 1;
		while (i >= 0)
		{
			loadedModules[i]->Dispose();
			SafeRelease(&loadedModules[i]);

			i--;
		}

		librarys->Dispose();
		SafeRelease(&librarys);
	}
	#pragma endregion

	#pragma region Member - Run/Exit
	void Engine::Run()
	{
		int wait = 0;
		LARGE_INTEGER freq;
		LARGE_INTEGER last;
		LARGE_INTEGER current;
		double gameTime = 0;

		if (!QueryPerformanceFrequency(&freq))
		{
			MessageBox(window->GetHWND(), L"No performance-counter found.", L"TikiEngine 2.0", MB_ICONERROR);
			return;
		}
		QueryPerformanceCounter(&last);

		while (window->GetReady())
		{
			window->Begin();

			QueryPerformanceCounter(&current);
			GameTime time = GameTime(
				(double)(current.QuadPart - last.QuadPart) / freq.QuadPart,				
				gameTime
			);
			gameTime += time.ElapsedTime;
			last = current;

			UpdateArgs args = UpdateArgs(time);
			input->Begin();
			input->FillInputState(&args.Input);
			content->Begin();
			physics->Begin();

			this->Update(args);

			physics->End(args);
			content->End();
			input->End();

			UInt32 i = 0;
			while (i < scene->GetCameras()->Count())
			{
				DrawArgs drawArgs = DrawArgs(
					time,
					scene->GetCameras()->Get(i),
					graphics,
					sprites,
					args,
					scene->GetLighting()
				);
				
				graphics->Begin(drawArgs);
				sprites->Begin();
				this->Draw(drawArgs);
				sprites->End();
				graphics->End();

				i++;
			}

			if (args.Input.GetKey(KEY_ESCAPE)) this->Exit();
			window->End();
		}
	}

	void Engine::Exit()
	{
		DestroyWindow(window->GetHWND());
	}
	#pragma endregion

	#pragma region Member - Scene
	Scene* Engine::GetScene() const
	{
		return scene;
	}

	void Engine::SetScene(Scene* scene)
	{
		this->scene = scene;

		if (!scene->IsInitialized())
		{
			InitializationArgs initArgs = InitializationArgs(content);
			scene->Initialize(initArgs);
		}
	}
	#pragma endregion

	#pragma region Member - Draw/Update
	void Engine::Draw(const DrawArgs& args)
	{
		if (scene)
		{
			scene->Draw(args);
		}
	}

	void Engine::Update(const UpdateArgs& args)
	{
		std::wostringstream s;
		s << "TikiEngine 2.0 - FPS: " << (1.0f / args.Time.ElapsedTime);

		wstring str = s.str();

		SetWindowText(
			window->GetHWND(),
			str.c_str()
		);

		if (args.Input.GetKeyPressed(KEY_F11))
		{
			desc.Graphics.Fullscreen = !desc.Graphics.Fullscreen;
			graphics->Reset();
		}

		if (scene)
		{
			scene->Update(args);
		}
	}
	#pragma endregion

	#pragma region Private Member
	bool Engine::initModule(IModule* module)
	{
		if (module != 0)
		{
			if (!module->Initialize(desc)) return false;

			loadedModules.Add(module);
			return true;
		}

		return false;
	}
	#pragma endregion
}
