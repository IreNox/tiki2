
#include "Game/SceneTim.h"

#include "Core/IMeshRenderer.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Core/MeshIndexed.h"

#include "Core/DefaultVertex.h"


namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Components;

		SceneTim::SceneTim(Engine* engine)
			: Scene(engine)
		{
		}

		SceneTim::~SceneTim()
		{
		}

		void SceneTim::Initialize(const InitializationArgs& args)
		{
			GameObject* go = new GameObject(engine);

			Mesh* mesh = engine->content->LoadMesh(L"Data/Resources/Normals.fbx"); //new MeshIndexed(engine);

			//DefaultVertex vertices[] = {
			//	{-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
			//	{ 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
			//	{ 1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
			//	{-1.0f,  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
			//	{-1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
			//	{ 1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
			//	{ 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
			//	{-1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f}
			//};

			//UINT indices[] = {
			//	0, 1, 2,
			//	0, 2, 3,
			//	4, 0, 3,
			//	4, 3, 7,
			//	1, 5, 6,
			//	1, 6, 2,
			//	3, 4, 6,
			//	3, 6, 7,
			//	4, 5, 1,
			//	4, 1, 0,
			//	5, 4, 7,
			//	5, 7, 6
			//};

			//mesh->SetVertexData(vertices, sizeof(vertices));
			//mesh->SetIndexData(indices, sizeof(indices));
			//mesh->SetVertexDeclaration(DefaultVertex::Declaration, 3);

			ITexture* tex = engine->content->LoadTexture(L"Data\\Resources\\jumppad_diff.jpg");

			Material* mat = engine->content->LoadMaterial(L"Data\\Effects\\os_default.fx");
			mat->GetShader()->SetTexture("tex", tex);

			IMeshRenderer* render = engine->librarys->CreateComponent<IMeshRenderer>(go);
			render->SetMesh(mesh);
			render->SetMaterial(mat);

			go->AddComponent(render);

			this->AddElement(go);

			light = new LightObject(engine);
			light->GetLight()->SetColor(Color::Green);
			light->GetLight()->SetRange(10);

			this->AddElement(light);
			this->AddElement(new CameraObject(engine));

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
			light->PRS.Position = Vector3(
				sinf(args.Time.TotalTime / 5) * 5,
				0,
				cosf(args.Time.TotalTime / 5) * 5
			);

			Scene::Update(args);
		}
	}
}