
#include "Core/Engine.h"

#include "Core/Scene.h"

#include "Core/Mutex.h"
#include "Core/Thread.h"

#include "Core/WindowModule.h"
#include "Core/LibraryManager.h"

#include "Core/IInput.h"
#include "Core/IPhysics.h"
#include "Core/IGraphics.h"
#include "Core/ISoundSystem.h"
#include "Core/ISpriteBatch.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

#include <math.h>
#include <string>
#include <sstream>
#include <time.h>
#include <ppl.h>

int bla = 1;

namespace TikiEngine
{
	using namespace Concurrency;

	#pragma region Class
	Engine::Engine()
		: scene(0), loadedModules(), state(), desc(), input(0), sound(0), physics(0), graphics(0), sprites(0), content(0)
	{
		srand((UInt32)time(0));
	}

	Engine::~Engine()
	{
	}
	#pragma endregion

	#pragma region Member - Init
	bool Engine::Initialize(EngineDescription& desc)
	{
		this->desc = desc;

		#pragma region Modules
		window = new WindowModule(this);
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
		#pragma endregion

		#pragma region Threading
		//function<void(void*)> funcDraw = &;
		//function<void(void*)> funcUpdate = &;

		//threadDraw = new Thread<Engine>(&Engine::Draw);
		//threadUpdate = new Thread<Engine>(&Engine::Update);

		//csDraw = new Mutex();
		//csUpdate = new Mutex();
		//csEngine = new Mutex();
		#pragma endregion

		return true;
	}
	#pragma endregion

	#pragma region Member - Dispose
	void Engine::Dispose()
	{
		SafeRelease(&scene);

		//SafeRelease(&threadDraw);
		//SafeRelease(&threadUpdate);
		//SafeRelease(&csDraw);
		//SafeRelease(&csUpdate);
		//SafeRelease(&csEngine);

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
				
		//threadUpdate->Start(this, 0);
		//threadDraw->Start(this, 0);

		UpdateArgs updateArgs0 = UpdateArgs(state.CurrentTime);
		UpdateArgs updateArgs1 = UpdateArgs(state.CurrentTime);
		state.UpdateState[0] = &updateArgs0;
		state.UpdateState[1] = &updateArgs1;

		auto funcDraw = make_task([=]{ this->Draw(); });
		auto funcUpdate = make_task([=]{ this->Update(); });

		while (window->GetReady())
		{
			window->Begin();

			//Mutex::WaitForMultiple(csDraw, 2);
			//OutputDebugString(L"Engine\n");

			QueryPerformanceCounter(&current);
			double elapsedTime = (double)(current.QuadPart - last.QuadPart) / freq.QuadPart;
			elapsedTime = (elapsedTime > 1 ? 1 : elapsedTime);
			gameTime += elapsedTime;

			GameTime time = GameTime(elapsedTime, gameTime);
			last = current;

			std::wostringstream s;
			s << "TikiEngine 2.0 - FPS: " << (1.0f / elapsedTime);

			wstring str = s.str();
			SetWindowText(window->GetHWND(), str.c_str());

			state.Swap(time);

#ifdef TIKI_MULTITHREADING

			structured_task_group tg;
			tg.run(funcUpdate);
			tg.run_and_wait(funcDraw);
#else
			this->Update();
			this->Draw();
#endif

			//csEngine->Unlock();
			//csUpdate->Unlock();
			//csDraw->Unlock();

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
		SafeRelease(&this->scene);
		SafeAddRef(scene, &this->scene);

		if (!scene->IsInitialized())
		{
			InitializationArgs initArgs = InitializationArgs(content);
			scene->Initialize(initArgs);
		}
	}
	#pragma endregion

	#pragma region Member - Draw/Update
	void Engine::Draw()
	{
		//while (state.Running)
		//{
			//OutputDebugString(L"Draw\n");

			UInt32 i = 0;
			while (i < scene->GetCameras()->Count())
			{
				DrawArgs drawArgs = DrawArgs(
					state.CurrentTime,
					scene->GetCameras()->Get(i),
					graphics,
					sprites,
					*state.UpdateState[state.DrawIndex],
					scene->GetLighting()
				);

				graphics->Begin(drawArgs);
				sprites->Begin();

				if (scene)
				{
					scene->Draw(drawArgs);
				}

				sprites->End();
				graphics->End();

				i++;
			}

			//csDraw->Unlock();
			//csEngine->Wait();
		//}
	}

	void Engine::Update()
	{
		//while (state.Running)
		//{
			//OutputDebugString(L"Update\n");

			// TODO: 
			//if (args.Input.GetKeyPressed(KEY_F11))
			//{
			//	desc.Graphics.Fullscreen = !desc.Graphics.Fullscreen;
			//	graphics->Reset();
			//}

			UpdateArgs args = UpdateArgs(state.CurrentTime);

			input->Begin();
			input->FillInputState(&args.Input);
			content->Begin();
			physics->Begin();

			if (scene)
			{
				scene->Update(args);
			}

			physics->End(args);
			content->End();
			input->End();

			if (args.Input.GetKey(KEY_ESCAPE)) this->Exit();

			*state.UpdateState[state.UpdateIndex] = args;

			//csUpdate->Unlock();
			//csEngine->Wait();
		//}
	}
	#pragma endregion

	#pragma region Private Member
	bool Engine::initModule(IModule* module)
	{
		if (module != 0)
		{
			module->AddRef();
			if (!module->Initialize(desc)) return false;

			loadedModules.Add(module);
			return true;
		}

		return false;
	}
	#pragma endregion
}
