
#include <math.h>
#include <string>
#include <sstream>
#include <direct.h>

#include "Core/Engine.h"
#include "Core/GarbageCollector.h"

#include "Core/Window.h"

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
		: scene(NULL)
	{
		char path[256];
		_getcwd(path, 256);

		this->workingDir = string(path);
	}

	Engine::~Engine()
	{
		if (scene != 0)
		{
			delete(scene);
			scene = 0;
		}

		if (graphics != 0)
		{
			delete(graphics);
			graphics = 0;
		}

		if (window != 0)
		{
			delete(window);
			window = 0;
		}
	}
	#pragma endregion

	#pragma region Member
	string Engine::GetWorkingDir()
	{
		return this->workingDir;
	}
	#pragma endregion

	#pragma region Member - Init
	bool Engine::Initialize(const EngineDescription& desc)
	{
		window = new Window(desc.hInst);
		if (!window->Initialize(&desc.Window))
		{
			MessageBox(window->GetHWND(), L"Can't create Window.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		//graphics = new Graphics(this);
		if (!graphics->Initialize(desc))
		{
			MessageBox(window->GetHWND(), L"Can't init Direct3D.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		//input = new Input(this);
		if (!input->Initialize(desc))
		{
			MessageBox(window->GetHWND(), L"Can't init Input.", L"TikiEngine 2.0", MB_ICONERROR);
			return false;
		}

		return true;
	}
	#pragma endregion

	#pragma region Member - Run
	void Engine::Run()
	{
		window->Show();
	
		LARGE_INTEGER freq;
		LARGE_INTEGER last;
		LARGE_INTEGER current;
		double gameTime = 0;

		if (!QueryPerformanceFrequency(&freq))
		{
			MessageBox(window->GetHWND(), L"No performance-counter found.", L"TikiEngine 2.0", MB_ICONERROR);
		}

		QueryPerformanceCounter(&last);

		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			QueryPerformanceCounter(&current);
			double elapsedTime = (double)(current.QuadPart - last.QuadPart) / freq.QuadPart;
			gameTime += elapsedTime;
			last = current;
			GameTime time = GameTime(elapsedTime, gameTime);

			UpdateArgs args = UpdateArgs(time);
			input->Begin();
			input->FillInputState(&args.Input);
			this->Update(args);
			input->End();

			DrawArgs drawArgs = DrawArgs(time, DrawContext(), graphics);

			this->Draw(drawArgs);

			GC::Collect();

			if (args.Input.GetKey(Key::ESCAPE))
			{
				DestroyWindow(window->GetHWND());
			}
		}
	}
	#pragma endregion

	#pragma region Member - Draw/Update
	void Engine::Draw(const DrawArgs& args)
	{
		graphics->Begin();

		if (scene)
		{
			scene->Draw(args);
		}

		graphics->End();
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
}