
#include "Core/Engine.h"
#include "Core/Scene.h"

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

namespace TikiEngine
{
	#pragma region Class
	Engine::Engine()
		: scene(0), loadedModules(), desc(), input(0), sound(0), physics(0), graphics(0), sprites(0), content(0), loadingScene(0),
		  isLoading(false), isLoadingFinish(true)
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

		loadingScene = new Scene(this);

		return true;
	}
	#pragma endregion

	#pragma region Member - Dispose
	void Engine::Dispose()
	{
		SafeRelease(&scene);
		SafeRelease(&loadingScene);

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

		if (!QueryPerformanceFrequency(&freq))
		{
			MessageBox(window->GetHWND(), L"No performance-counter found.", L"TikiEngine 2.0", MB_ICONERROR);
			return;
		}
		QueryPerformanceCounter(&last);
		
		srand((UInt32)(last.QuadPart / freq.QuadPart));

		UpdateArgs updateArgs = UpdateArgs();

		while (window->GetReady())
		{
			window->Begin();

			QueryPerformanceCounter(&current);
			double elapsedTime = (double)(current.QuadPart - last.QuadPart) / freq.QuadPart;
			elapsedTime = (elapsedTime > 1 ? 1 : elapsedTime);

			updateArgs.Time.TotalTime += elapsedTime;
			updateArgs.Time.ElapsedTime = elapsedTime;
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

			this->Update(updateArgs);
			this->Draw(updateArgs);

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
		SafeChangeRef(&this->scene, scene);

		if (!scene->IsInitialized())
		{
			isLoading = true;
			isLoadingFinish = false;
			
			loadingThread = new Thread<Engine, Scene>(&Engine::initScene);
			loadingThread->Start(this, scene);
		}
	}

	Scene* Engine::GetLoadingScene() const
	{
		return loadingScene;
	}

	void Engine::SetLoadingScene(Scene* scene)
	{
		SafeChangeRef(&loadingScene, scene);

		if (!loadingScene->IsInitialized())
		{
			InitializationArgs initArgs = InitializationArgs(content);
			loadingScene->Initialize(initArgs);
		}
	}
	#pragma endregion

	#pragma region Member - Draw
	void Engine::Draw(UpdateArgs& args)
	{
		Scene* curScene = scene;

		if (isLoading)
		{
			curScene = loadingScene;
		}

		UInt32 i = 0;
		UInt32 c = TIKI_MAX(1, curScene->GetCameras()->Count());
		while (i < c)
		{
			DrawArgs drawArgs = DrawArgs(
				args.Time,
				DM_Geometry,
				(i < curScene->GetCameras()->Count() ? curScene->GetCameras()->Get(i) : 0),
				graphics,
				sprites,
				args,
				curScene->GetLighting()
			);

			graphics->Begin(drawArgs);
			sprites->Begin();

			UInt32 bi = 0;
			UInt32 bc = 1 + (TIKI_SHADOWS_ENABLED ? 1 : 0);
			while (bi < bc)
			{
				if (bi != 0)
				{
					drawArgs.Mode = (DrawMode)bi;
					graphics->GetUnusedScreenTarget()->ApplyFirstAndOnly();
				}

				curScene->Draw(drawArgs);

				bi++;
			}

#if _DEBUG
			graphics->DrawConsole(drawArgs);
#endif

			sprites->End();
			graphics->End();

			i++;
		}
	}
	#pragma endregion

	#pragma region Member - Update
	void Engine::Update(UpdateArgs& args)
	{
		if (!isLoading)
		{
			input->Begin();
			input->FillInputState(&args.Input);
			content->Begin();
			physics->Begin();

			scene->Update(args);

			physics->End(args);
			content->End();
			input->End();

			if (args.Input.GetKeyPressed(KEY_F12))
			{
				graphics->MakeScreenshot();
			}

			if (args.Input.GetKeyPressed(KEY_ESCAPE)) 
			{
				this->Exit();
			}
		}
		else
		{
			critLoading.Lock();

			if (isLoadingFinish)
			{
				isLoading = false;
				SafeRelease(&loadingThread);
			}

			critLoading.Unlock();

			loadingScene->Update(args);
		}

		double wait = (1.0 / 60.0) - args.Time.ElapsedTime;

		if (wait > 0.0)
		{
			int milli = (int)(wait * 1000.0);
			Sleep(milli);
		}
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

	void Engine::initScene(Scene* scene)
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

		critLoading.Lock();
		isLoadingFinish = true;
		critLoading.Unlock();
	}
	#pragma endregion
}
