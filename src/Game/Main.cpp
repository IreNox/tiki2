
#include <Windows.h>

#include <Core/Engine.h>

#include "Core/Texture.h"
#include "Graphics/DefaultShader.h"

#include "Box.h"
#include "Core/Quad.h"
//#include "TeeTriangle.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	//TODO: 145, 149 = List
	//_CrtSetBreakAlloc(24334);

	{
		ENGINE_DESCRIPTION desc;

		desc.hInst = hInst;
		desc.Window.Width = 800;
		desc.Window.Height = 600;

		Engine* engine = new Engine();
		engine->Initialize(&desc);
		engine->scene = new Scene(engine);

		Texture* texture = new Texture(
			engine,
			wstring(L"Data/Resources/box_diffuse.jpg")
		);

		Shader* shader = new DefaultShader(engine);
		shader->GetVariable("tex").SetTexture(texture);

		//Shader* shaderPP = new Shader(engine, L"Data/Effects/pp_default.fx");
		//Quad* quad = new Quad(engine, shaderPP);


		engine->scene->AddElement(new Box(engine, shader));
		//scene->AddElement(new TeeTriangle(engine));

		engine->Run();

		delete(shader);
		delete(texture);

		delete(engine);
	}

	_CrtDumpMemoryLeaks();

	return 0;
}