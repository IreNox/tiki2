
#include <Windows.h>

#include "Core/Engine.h"

#include "Game/SceneTim.h"
#include "Game/SceneMark.h"
#include "Game/SceneAdrian.h"
#include "Game/SceneLevel.h"

using namespace TikiEngine;
using namespace TikiEngine::Game;
using namespace TikiEngine::Description;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	//TODO: 141 = KA; 23977 = font; 712/713 = Spritebatch
	//_CrtSetBreakAlloc(98954);

	{
		EngineDescription desc;

		desc.hInst = hInst;
		desc.Window.Width = 1100;
		desc.Window.Height = 750;

		Engine* engine = new Engine();
		
		if (engine->Initialize(desc))
		{
			DWORD buffer;
			WCHAR username[100];
			GetUserName(username, &buffer);
			
			wstring name = username;

			if ((name == L"tim.boden" || name == L"Der Hans von Morgen" || name == L"Tim") && false)
			{
				engine->scene = new SceneTim(engine);
				//engine->scene = new SceneAdrian(engine);
				//engine->scene = new SceneMark(engine);
			}
			else if (name == L"adrian.l�ck" || name == L"Adrian")
			{
				engine->scene = new SceneAdrian(engine);
			}
			else if (name == L"mark.reichert" || name == L"Shekk")
			{				
				engine->scene = new SceneMark(engine);
				//engine->scene = new SceneTim(engine);
				//engine->scene = new SceneAdrian(engine);
			}
			else
			{
				SceneLevel* level = new SceneLevel(engine);
				level->LoadLevel(1);

				engine->scene = level;
			}

			engine->Run();
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
