
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
	//TODO: 141 = KA; 23977 = font; 712/713 = Spritebatch
	//_CrtSetBreakAlloc(13305);

	{
		EngineDescription desc;

		desc.hInst = hInst;
		desc.Window.Width = 1100;
		desc.Window.Height = 750;
		desc.Window.Icon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

		Engine* engine = new Engine();
		
		if (engine->Initialize(desc))
		{
			Scene* scene = 0;
				
			DWORD buffer;
			WCHAR username[100];
			GetUserName(username, &buffer);

			wstring name = username;

			if (name == L"tim.boden")
			{
				scene = new SceneTim(engine);
				//scene = new SceneLevel(engine);
				//((SceneLevel*)scene)->LoadLevel(1);
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
	OutputDebugString(L"==Memory Leaks Begin==\n");
	_CrtDumpMemoryLeaks();
	OutputDebugString(L"==Memory Leaks End==\n");
#endif

	return 0;
}
