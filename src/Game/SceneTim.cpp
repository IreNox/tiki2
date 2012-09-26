
#include "Game/SceneTim.h"

#include "Core/Engine.h"
#include "Core/IPhysics.h"
#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"
#include "Core/ISoundSystem.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Core/IMeshRenderer.h"
#include "Core/IPhysicsMaterial.h"
#include "Core/IBoxCollider.h"
#include "Core/ITerrainRenderer.h"
#include "Core/ISound.h"

#include "Game/CameraFly.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Scripts;
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
			
			Mesh* mesh = engine->content->LoadMesh(L"Data/Resources/Models/Normals.fbx");
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
			light->PRS.Position = Vector3(5, 0, 0);

			this->AddElement(light);
			light->Release();

			go = new CameraObject(engine);
			go->PRS.Position.Z = 40.0f;

			CameraFly* fly = new CameraFly(engine, go);
			go->AddComponent(fly);
			fly->Release();

			this->AddElement(go);
			go->Release();

			go = new GameObject(engine);
			
			ITerrainRenderer* terrain = engine->librarys->CreateComponent<ITerrainRenderer>(go);
			go->AddComponent(terrain);
			terrain->Release();

			this->AddElement(go);
			go->Release();

			//engine->graphics->AddPostProcess(new PPBlur(engine));

			ssao = new PPScreenSpaceAmbientOcclusion(engine);
			engine->graphics->AddPostProcess(ssao);

			ISound* sound = engine->librarys->CreateResource<ISound>();
			sound->LoadFromFile(L"Data/Sound/beep.wav");

			//font = engine->librarys->CreateResource<IFont>();
			//font->Create(L"Arial", 16.0f);

			Scene::Initialize(args);
		}

		void SceneTim::Draw(const DrawArgs& args)
		{
			engine->graphics->GetDepthTarget()->Clear(Color::Black);
			engine->graphics->GetDepthTarget()->Apply(1);
			engine->graphics->GetNormalTarget()->Clear(Color::NormalDefault);
			engine->graphics->GetNormalTarget()->Apply(2);

			Scene::Draw(args);

			//engine->sprites->DrawString(font, L"BlaBla", Vector2(500, 500));

			engine->sprites->Draw(
				engine->graphics->GetDepthTarget(),
				Rectangle(10, 10, 200, 180)
			);

			engine->sprites->Draw(
				engine->graphics->GetNormalTarget(),
				Rectangle(10, 200, 200, 180)
			);

			engine->sprites->Draw(
				ssao->GetAO(),
				Rectangle(10, 390, 200, 180)
			);

			/*engine->sprites->Draw(
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
