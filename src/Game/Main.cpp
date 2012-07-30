
#include <Windows.h>

#include "Core/Engine.h"
#include "Core/Scene.h"

//#include "Core/Texture.h"
//#include "Graphics/DefaultShader.h"

#include "Box.h"
#include "Core/QuadObject.h"
//#include "TeeTriangle.h"

using namespace TikiEngine;
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
		engine->Initialize(desc);
		engine->scene = new Scene(engine);

		//ITexture* tex = engine->content->LoadTexture(L"Data\\Resources\\box_diffuse.jpg");

		//Texture* texture = new Texture(
		//	engine,
		//	wstring(L"Data/Resources/box_diffuse.jpg")
		//);

		//Shader* shader = new DefaultShader(engine);
		//shader->GetVariable("tex").SetTexture(texture);

		//Shader* shaderPP = new Shader(engine, L"Data/Effects/pp_default.fx");
		//Quad* quad = new Quad(engine, shaderPP);


		//engine->scene->AddElement(new Box(engine, shader));
		//scene->AddElement(new TeeTriangle(engine));

		engine->Run();

		//delete(shader);
		//delete(texture);

		delete(engine);
	}

	_CrtDumpMemoryLeaks();

	return 0;
}