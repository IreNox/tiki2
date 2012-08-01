
#include "Game/SceneTim.h"

namespace TikiEngine
{
	namespace Game
	{
		SceneTim::SceneTim(Engine* engine)
			: Scene(engine)
		{
		}

		SceneTim::~SceneTim()
		{
		}

		void SceneTim::Initialize(const InitializationArgs& args)
		{
			ITexture* tex = engine->content->LoadTexture(L"Data\\Resources\\box_diffuse.jpg");

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

			Scene::Initialize(args);
		}

		void SceneTim::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);
		}

		void SceneTim::Update(const UpdateArgs& args)
		{
			Scene::Update(args);
		}
	}
}