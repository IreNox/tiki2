
#include "Game/SceneTim.h"

#include "Core/IPhysics.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Core/IMeshRenderer.h"
#include "Core/IPhysicsMaterial.h"
#include "Core/IBoxCollider.h"
#include "Core/DebugPhysicsRenderer.h"

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

			Mesh* mesh = engine->content->LoadMesh(L"Data/Resources/Normals.fbx");
			ITexture* tex = engine->content->LoadTexture(L"Data\\Resources\\jumppad_diff.jpg");

			Material* mat = engine->content->LoadMaterial(L"Data\\Effects\\os_default.fx");
			mat->GetShader()->SetTexture("tex", tex);

			IMeshRenderer* render = engine->librarys->CreateComponent<IMeshRenderer>(go);
			render->SetMesh(mesh);
			render->SetMaterial(mat);

			mat->Release();
			mesh->Release();

			go->AddComponent(render);
			render->Release();

			this->AddElement(go);
			go->Release();

			light = new LightObject(engine);
			light->GetLight()->SetColor(Color::Green);
			light->GetLight()->SetRange(10);

			this->AddElement(light);
			light->Release();

			go = new CameraObject(engine);
			this->AddElement(go);
			go->Release();



			//////////////////////////////////////////////////////////////////////////
			// OLD
			//////////////////////////////////////////////////////////////////////////
			//go = new GameObject(engine);

			//IPhysicsMaterial* material; 
			//material = engine->content->LoadPhysicsMaterial(L"TODO");
			//material->SetRestitution(1.0f);
			//material->SetDynamicFriction(0.5f);
			//material->SetStaticFriction(0.5f); // static friction may be higher than 1.

			//// init
			//IBoxCollider* box = engine->librarys->CreateComponent<IBoxCollider>(go);
			//box->SetMaterial(material->GetIndex()); // 0 = default material	
			//box->SetCenter(Vector3(5, 5, 0));
			//box->SetSize(Vector3(1, 1, 1));
			//box->SetDynamic(true);
			//box->GetRigidBody()->SetKinematic(true);
			//	
			//this->AddElement(go);

			//go = new DebugPhysicRenderer(engine);
			//this->AddElement(go);

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

			Scene::Initialize(args);
		}

		void SceneTim::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);
		}

		void SceneTim::Update(const UpdateArgs& args)
		{
			light->PRS.Position = Vector3(
				sinf((float)args.Time.TotalTime / 5) * 5,
				0,
				cosf((float)args.Time.TotalTime / 5) * 5
			);

			Scene::Update(args);
		}
	}
}