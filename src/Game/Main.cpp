
#include <Windows.h>

#include "Core/Engine.h"
#include "Game/SceneMenuMain.h"

#include "../misc/res/resource.h"

using namespace TikiEngine;
using namespace TikiEngine::Game;
using namespace TikiEngine::Description;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	//TODO: 141 = KA; 23977 = font; 712/713 = Spritebatch
	//_CrtSetBreakAlloc(11171);

	{
		EngineDescription desc;

		desc.hInst = hInst;
		desc.Window.Width = 1100;
		desc.Window.Height = 750;
		desc.Window.Icon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

		Engine* engine = new Engine();
		
		if (engine->Initialize(desc))
		{
			DWORD buffer;
			WCHAR username[100];
			GetUserName(username, &buffer);
			
			wstring name = username;

			//if ((name == L"tim.boden" || name == L"Der Hans von Morgen" || name == L"Tim") && false)
			//{
			//	engine->scene = new SceneTim(engine);
			//	//engine->scene = new SceneAdrian(engine);
			//	//engine->scene = new SceneMark(engine);
			//}
			//else if (name == L"adrian.lück" || name == L"Adrian")
			//{
			//	//engine->scene = new SceneTim(engine);
			//	engine->scene = new SceneAdrian(engine);
			//	//engine->scene = new SceneMark(engine);
			//}
			//else if (name == L"mark.reichert" || name == L"Mark.Reichert" || name == L"Shekk")
			//{				
			//	engine->scene = new SceneMark(engine);
			//	//engine->scene = new SceneTim(engine);
			//	//engine->scene = new SceneAdrian(engine);
			//}
			//else
			{
				engine->SetScene(
					new SceneMenuMain(engine)
				);
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
