
#include "Game/SceneTim.h"

#include "Core/IPhysics.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Core/IMeshRenderer.h"
#include "Core/IPhysicsMaterial.h"
#include "Core/IBoxCollider.h"
#include "Core/DebugPhysicsRenderer.h"

#include "Game/PPBlur.h"

#include "Game/CameraFly.h"

#include "Core/Engine.h"
#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Scripts;
		using namespace TikiEngine::Graphics;
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Components;

		SceneTim::SceneTim(Engine* engine)
			: Scene(engine)
		{
		}

		SceneTim::~SceneTim()
		{
			SafeRelease(&tex);
			SafeRelease(&font);
		}

		void SceneTim::Initialize(const InitializationArgs& args)
		{
			GameObject* go = new GameObject(engine);
			
			Mesh* mesh = engine->content->LoadMesh(L"Data/Resources/Models/tim_test.FBX");
			tex = engine->content->LoadTexture(L"Data/Resources/Textures/jumppad_diff.jpg");

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
			light->GetLight()->SetColor(Color(0.8f, 0.8f, 0.8f, 0.8f));
			light->GetLight()->SetRange(7.5f);
			light->PRS.Position = Vector3(50, 0, 0);

			this->AddElement(light);
			light->Release();

			go = new CameraObject(engine);
			go->PRS.Position.Z = 40.0f;

			CameraFly* fly = new CameraFly(engine, go);
			go->AddComponent(fly);
			fly->Release();

			this->AddElement(go);
			go->Release();


			//engine->graphics->AddPostProcess(new PPBlur(engine));


			font = engine->librarys->CreateResource<IFont>();
			font->Create(L"Arial", 16.0f);

			Scene::Initialize(args);
		}

		void SceneTim::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);

			engine->sprites->DrawString(font, L"BlaBla", Vector2(100, 100));

			/*engine->sprites->Draw(
				tex,
				Vector2(400, 400),
				args.Time.TotalTime,
				Vector2(256, 256),
				Vector2(0.5f),
				2
			);

			engine->sprites->Draw(
				tex,
				Vector2(300, 300),
				args.Time.TotalTime,
				Vector2(256, 256),
				Vector2(1),
				1
			);*/
		}

		void SceneTim::Update(const UpdateArgs& args)
		{
			light->PRS.Position = Vector3(
				sinf((float)args.Time.TotalTime / 5) * 50,
				0,
				cosf((float)args.Time.TotalTime / 5) * 50
			);

			//elements[0]->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(args.Time.TotalTime, 0, 0);

			Scene::Update(args);
		}
	}
}