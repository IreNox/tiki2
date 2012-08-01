
#include <Windows.h>

#include "Core/Engine.h"

//#include "Core/Texture.h"
//#include "Graphics/DefaultShader.h"

#include "Box.h"
#include "Core/QuadObject.h"
//#include "TeeTriangle.h"

#include "Game/SceneTim.h"
#include "Game/SceneMark.h"
#include "Game/SceneAdrian.h"

using namespace TikiEngine;
using namespace TikiEngine::Game;
using namespace TikiEngine::Description;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	//TODO: 141 = KA
	//_CrtSetBreakAlloc(45514);

	{
		EngineDescription desc;

		desc.hInst = hInst;
		desc.Window.Width = 800;
		desc.Window.Height = 600;

		Engine* engine = new Engine();
		
		if (engine->Initialize(desc))
		{
			DWORD buffer;
			WCHAR username[100];
			GetUserName(username, &buffer);

			wstring name = username;

			if (name == L"tim.boden")
			{
				engine->scene = new SceneTim(engine);
			}
			else if (name == L"adrian.l�ck")
			{
				engine->scene = new SceneAdrian(engine);
			}
			else if (name == L"mark.reichert")
			{
				engine->scene = new SceneMark(engine);
			}

			engine->Run();
		}

		delete(engine);
	}

	_CrtDumpMemoryLeaks();

	return 0;
}