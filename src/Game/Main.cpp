
#include <Windows.h>

#include "Core/Engine.h"
#include "Game/SceneMenuMain.h"
#include "Game/SceneAdrian.h"
#include "Game/SceneMark.h"
#include "Game/SceneTim.h"
#include "Game/SceneLevel.h"

#include "../misc/res/resource.h"

using namespace TikiEngine;
using namespace TikiEngine::Game;
using namespace TikiEngine::Description;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	//_CrtSetBreakAlloc(1670);

	{
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
			Scene* scene = 0;
				
			DWORD buffer;
			WCHAR username[100];
			GetUserName(username, &buffer);

			wstring name = username;

			if ((name == L"tim.boden" || name == L"Tim") && false)
			{
				//scene = new SceneTim(engine);

				scene = new SceneLevel(engine);
				engine->SetScene(scene);
				((SceneLevel*)scene)->LoadLevel(1);
			}
			else if((name == L"adrian.lück" || name == L"Adrian") && false)
			{
				scene = new SceneAdrian(engine);
			}
			else
			{
				scene = new SceneMenuMain(engine);
			}
			scene->AddRef();

			engine->SetScene(scene);
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
