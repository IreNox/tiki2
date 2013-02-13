
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

#pragma region GetStartScene
inline Scene* GetStartScene(Engine* engine)
{
#if _DEBUG
	DWORD buffer;
	WCHAR username[100];
	GetUserName(username, &buffer);
	::TikiEngine::wstring name = username;

	Scene* scene;

	if ((name == L"tim.boden" || name == L"Tim") && false)
	{
		//scene = TIKI_NEW SceneTim(engine);
		//scene = TIKI_NEW SceneMark(engine);
		//scene = TIKI_NEW SceneAdrian(engine);

		scene = TIKI_NEW SceneLevel(engine);
		((SceneLevel*)scene)->LoadLevel(1);
	}
	else if((name == L"adrian.lück" || name == L"Adrian") && true)
	{
		scene = TIKI_NEW SceneAdrian(engine);
	}
	else if((name == L"Mark.Reichert" || name == L"Shekk") && false)
	{
		scene = TIKI_NEW SceneMark(engine);
	}
	else
	{
		scene = TIKI_NEW SceneMenuMain(engine);
	}

	return scene;
#else
	return TIKI_NEW SceneMenuMain(engine);
#endif
}
#pragma endregion

#pragma region WinMain
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	//_CrtSetBreakAlloc(24035);

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
		desc.Graphics.UseShadows = true;

		desc.IgnoreModules.Add(L"tikiengine.graphicsdx10.dll");
		//desc.IgnoreModules.Add(L"tikiengine.graphicsdx11.dll");
		desc.IgnoreModules.Add(L"tikiengine.graphicsogl.dll");

#if !_DEBUG
		//desc.Graphics.Fullscreen = true;
#endif

		Engine* engine = TIKI_NEW Engine();
		
		if (engine->Initialize(desc))
		{
			Scene* scene = GetStartScene(engine);
			scene->AddRef();

			//engine->SetLoadingScene(TIKI_NEW SceneLoading(engine));
			engine->SetScene(scene);

#if _DEBUG
			double el = time.Stop();

			engine->HLog.Write(
				::TikiEngine::string("Complete Loading: ") + StringConvert::ToString(el) + " sec",
				false
			);
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
#pragma endregion