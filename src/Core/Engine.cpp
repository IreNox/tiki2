
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

#include "Core/HelperLog.h"
#include "Core/HelperThreading.h"

#include "Core/TikiPerformanceCounter.h"

#include <math.h>
//#include <time.h>
//#include <ppl.h>

namespace TikiEngine
{
	//using namespace Concurrency;

	#pragma region Class
	Engine::Engine()
		: scene(0), loadedModules(), state(), desc(), input(0), sound(0), physics(0), graphics(0), sprites(0), content(0)
#if _DEBUG
		, fpsMin(1000000000), fpsMax(0), fpsIndex(0), fpsAve(0)
#endif
	{
	}

	Engine::~Engine()
	{
	}
	#pragma endregion

	#pragma region Member - Init
	bool Engine::Initialize(EngineDescription& desc)
	{
		this->desc = desc;

		#pragma region Database
		sqlite3_open(
			StringWtoA(this->HPath.CombineWorkingPath(L"Data/TikiData.sqlite")).c_str(),
			&dataBase
		);
		#pragma endregion

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

		if (dataBase != 0)
		{
			sqlite3_close(dataBase);
			dataBase = 0;
		}
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
		
		srand((UInt32)(last.QuadPart / freq.QuadPart));

		//threadUpdate->Start(this, 0);
		//threadDraw->Start(this, 0);

		state.UpdateState = UpdateArgs(state.CurrentTime);

#ifdef TIKI_MULTITHREADING
		state.UpdateState = UpdateArgs(state.CurrentTime);

		auto funcDraw = make_task([=]{ this->Draw(0); });
		auto funcUpdate = make_task([=]{ this->Update(0); });
#endif

		while (window->GetReady())
		{
			window->Begin();

			//Mutex::WaitForMultiple(csDraw, 2);

			QueryPerformanceCounter(&current);
			double elapsedTime = (double)(current.QuadPart - last.QuadPart) / freq.QuadPart;
			elapsedTime = (elapsedTime > 1 ? 1 : elapsedTime);
			gameTime += elapsedTime;

			GameTime time = GameTime(elapsedTime, gameTime);
			last = current;

#if _DEBUG
			double fps = 1.0 / elapsedTime;
			if (fps < fpsMin) fpsMin = fps;
			if (fps > fpsMax) fpsMax = fps;
			fpsAve = (fpsCache[0] + fpsCache[1] + fpsCache[2] + fpsCache[3] + fpsCache[4] + fps) / 6.0; 
			fpsIndex = (++fpsIndex) % 5;
			fpsCache[fpsIndex] = fps;

			std::wostringstream s;
			s << "TikiEngine 2.0 - FPS - Min: " << fpsMin << " - Max: " << fpsMax << " - Average: " << fpsAve;

			wstring str = s.str();
			SetWindowText(window->GetHWND(), str.c_str());
#else
			std::wostringstream s;
			s << "TikiEngine 2.0 - FPS: " << (1.0 / elapsedTime);
			SetWindowText(window->GetHWND(), s.str().c_str());
#endif

			state.Swap(time);

#ifdef TIKI_MULTITHREADING
			HelperThreading::Swap();

			structured_task_group tg;
			tg.run(funcUpdate);
			tg.run_and_wait(funcDraw);
#else
			this->Update(0);
			this->Draw(0);
#endif

			//csEngine->Unlock();
			//csUpdate->Unlock();
			//csDraw->Unlock();

			// TODO: Fullscreen
			//if (args.Input.GetKeyPressed(KEY_F11))
			//{
			//	desc.Graphics.Fullscreen = !desc.Graphics.Fullscreen;
			//	graphics->Reset();
			//}
			
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
#if _DEBUG
			TikiPerformanceCounter time;
			time.Start();
#endif

			InitializationArgs initArgs = InitializationArgs(content);
			scene->Initialize(initArgs);

#if _DEBUG
			double el = time.Stop();

			ostringstream s;
			s << "LoadScene: " << typeid(*scene).name() << " - ElapsedTime: " << el;

			HLog.Write(s.str(), false);
#endif
		}
	}
	#pragma endregion

	#pragma region Member - Draw/Update
	void Engine::Draw(void*)
	{		
		//HelperThreading::InitThread(state.DrawIndex);

		//while (state.Running)
		//{
			//csEngine->Wait();

			//ostringstream s;
			//s << "Camera Count: " << scene->GetCameras()->Count();

			//HelperLog::Write(s.str());

			UInt32 i = 0;
			while (i < scene->GetCameras()->Count())
			{
				DrawArgs drawArgs = DrawArgs(
					state.CurrentTime,
					DM_Geometry,
					scene->GetCameras()->Get(i),
					graphics,
					sprites,
					state.UpdateState,
					scene->GetLighting()
				);

				graphics->Begin(drawArgs);
				sprites->Begin();

				UInt32 b = 0;
				while (b < 1)
				{
					if (b != 0)
					{
						drawArgs.Mode = (DrawMode)b;
						graphics->GetUnusedScreenTarget()->ApplyFirstAndOnly();
					}

					if (scene)
					{
						scene->Draw(drawArgs);
					}

					b++;
				}

#if _DEBUG
				graphics->DrawConsole(drawArgs);
#endif

				sprites->End();
				graphics->End();

				i++;
			}

			//csEngine->Wait();
			//csDraw->Unlock();
			//threadDraw->Suspend();
		//}
	}

	void Engine::Update(void*)
	{
		//HelperThreading::InitThread(state.UpdateIndex);

		//while (state.Running)
		//{
			//csEngine->Wait();

			//wostringstream s;
			//s << L"Update: " << HelperThreading::GIndex();

			//HLog(s.str().c_str());

			state.UpdateState = UpdateArgs(state.CurrentTime);

			input->Begin();
			input->FillInputState(&state.UpdateState.Input);
			content->Begin();
			physics->Begin();

			if (scene)
			{
				scene->Update(state.UpdateState);
			}

			physics->End(state.UpdateState);
			content->End();
			input->End();

			if (state.UpdateState.Input.GetKeyPressed(KEY_F12))
			{
				graphics->MakeScreenshot();
			}

			if (state.UpdateState.Input.GetKeyPressed(KEY_ESCAPE)) 
			{
				this->Exit();
			}

			double wait = (1.0 / 60.0) - state.CurrentTime.ElapsedTime;

			if (wait > 0.0)
			{
				int milli = (int)(wait * 1000.0);
				Sleep(milli);
			}

			//state.UpdateState = args;

			//csUpdate->Unlock();
			//threadUpdate->Suspend();
		//}
	}
	#pragma endregion

	#pragma region Private Member
	bool Engine::initModule(IModule* module)
	{
		if (module != 0)
		{
#if _DEBUG
			LARGE_INTEGER freq;
			LARGE_INTEGER start;
			LARGE_INTEGER end;

			QueryPerformanceFrequency(&freq);
			QueryPerformanceCounter(&start);
#endif

			module->AddRef();
			if (!module->Initialize(desc)) return false;

			loadedModules.Add(module);

#if _DEBUG
			QueryPerformanceCounter(&end);
			
			ostringstream s;
			s << "Loading Module: " << typeid(*module).name() << " - Elapsed Time: " << ((double)(end.QuadPart - start.QuadPart) / freq.QuadPart); 

			this->HLog.Write(s.str(), false);
#endif

			return true;
		}

		return false;
	}
	#pragma endregion
}
