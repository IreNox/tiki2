
#include "Core/Engine.h"
#include "Core/TikiPerformanceCounter.h"

#include "Game/SceneMenuMain.h"
#include "Game/SceneAdrian.h"
#include "Game/SceneMark.h"
#include "Game/SceneTim.h"
#include "Game/SceneLevel.h"
#include "Game/SceneLoading.h"

#include "../misc/res/resource.h"

using namespace TikiEngine;
using namespace TikiEngine::Game;
using namespace TikiEngine::Description;

inline Scene* GetStartScene(Engine* engine)
{
#if _DEBUG
	DWORD buffer;
	WCHAR username[100];
	GetUserName(username, &buffer);
	wstring name = username;

	Scene* scene;

	if ((name == L"tim.boden" || name == L"Tim") && true)
	{
		//scene = new SceneTim(engine);
		//scene = new SceneMark(engine);
		//scene = new SceneAdrian(engine);

		scene = new SceneLevel(engine);
		((SceneLevel*)scene)->LoadLevel(1);
	}
	else if((name == L"adrian.lück" || name == L"Adrian") && false)
	{
		scene = new SceneAdrian(engine);
	}
	else if((name == L"Mark.Reichert" || name == L"Shekk") && false)
	{
		scene = new SceneMark(engine);
	}
	else
	{
		scene = new SceneMenuMain(engine);
	}

	return scene;
#else
	return new SceneMenuMain(engine);
#endif
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	//_CrtSetBreakAlloc(1433);

	{
#if _DEBUG
		TikiPerformanceCounter time;
		time.Start();
#endif

		EngineDescription desc;
		
		desc.hInst = hInst;
		desc.Window.Width = 1100;
		desc.Window.Height = 750;
		desc.Window.Icon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

#if !_DEBUG
		desc.Graphics.Fullscreen = true;
#endif

		Engine* engine = new Engine();
		
		if (engine->Initialize(desc))
		{
			Scene* scene = GetStartScene(engine);
			scene->AddRef();

			engine->SetLoadingScene(new SceneLoading(engine));
			engine->SetScene(scene);

#if _DEBUG
			double el = time.Stop();

			ostringstream s;
			s << "Complete Loading: " << el << " sec";
			engine->HLog.Write(s.str(), false);
#endif

			engine->Run();

			SafeRelease(&scene);
		}
		
		engine->Dispose();
		delete(engine);
	}

#if _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
