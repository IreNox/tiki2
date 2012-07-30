
#include <math.h>
#include <string>
#include <sstream>

#include "Core/Engine.h"
#include "Core/GarbageCollector.h"

#include "Core/Window.h"
#include "Core/LibraryManager.h"

#include "Core/Scene.h"

#include "Core/IInput.h"
#include "Core/IPhysics.h"
#include "Core/IGraphics.h"

#include "Core/GameTime.h"
#include "Core/DrawContext.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	#pragma region Class
	Engine::Engine()
		: scene(0), loadedModules()
	{
	}

	Engine::~Engine()
	{
		if (scene != 0)
		{
			delete(scene);
			scene = 0;
		}

		loadedModules.Remove(librarys);

		int i = 0;
		while (i < loadedModules.Count())
		{
			loadedModules[i]->Dispose();
			delete(loadedModules[i]);

			i++;
		}

		librarys->Dispose();
		delete(librarys);
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

		graphics = librarys->CreateModule<IGraphics>();
		if (!initModule(graphics))
		{
			MessageBox(window->GetHWND(), L"Can't init Direct3D.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		input = librarys->CreateModule<IInput>();
		if (!initModule(input))
		{
			MessageBox(window->GetHWND(), L"Can't init Input.", L"TikiEngine 2.0", MB_ICONERROR);
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

	#pragma region Member - Run
	void Engine::Run()
	{
		LARGE_INTEGER freq;
		LARGE_INTEGER last;
		LARGE_INTEGER current;
		double gameTime = 0;

		if (!QueryPerformanceFrequency(&freq))
		{
			MessageBox(window->GetHWND(), L"No performance-counter found.", L"TikiEngine 2.0", MB_ICONERROR);
		}

		QueryPerformanceCounter(&last);

		while (window->GetReady())
		{
			window->Begin();

			QueryPerformanceCounter(&current);
			double elapsedTime = (double)(current.QuadPart - last.QuadPart) / freq.QuadPart;
			gameTime += elapsedTime;
			last = current;
			GameTime time = GameTime(elapsedTime, gameTime);

			UpdateArgs args = UpdateArgs(time);
			input->Begin();
			physics->Begin();

			input->FillInputState(&args.Input);

			this->Update(args);

			physics->End();
			input->End();

			DrawArgs drawArgs = DrawArgs(time, DrawContext(), graphics);

			graphics->Begin();
			this->Draw(drawArgs);
			graphics->End();

			GC::Collect();

			if (args.Input.GetKey(KEY_ESCAPE))
			{
				DestroyWindow(window->GetHWND());
			}

			window->End();
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