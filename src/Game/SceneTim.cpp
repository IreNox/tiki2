
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

#include "Game/CameraRTS.h"

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
			SafeRelease(&ssao);
			SafeRelease(&light);
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
			render->Release();

			this->AddElement(go);
			go->Release();

			light = new LightObject(engine);
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(750.0f);
			light->PRS.Position = Vector3(1500, 0, 0);
			this->AddElement(light);
			
			go = new CameraObject(engine);
			go->PRS.Position.Z = 500.0f;
			go->PRS.Position.Y = 300.0f;

			CameraRTS* fly = new CameraRTS(engine, go);
			fly->Release();

			this->AddElement(go);
			go->Release();

			go = new GameObject(engine);
			
			mat = engine->content->LoadMaterial(L"Data\\Effects\\os_cloddy.fx");
			mat->GetShader()->SetTexture("tex", tex);

			ITerrainRenderer* terrain = engine->librarys->CreateComponent<ITerrainRenderer>(go);
			terrain->Release();
			terrain->SetMaterial(mat);
			mat->Release();

			this->AddElement(go);
			go->Release();

			//engine->graphics->AddPostProcess(new PPBlur(engine));

			ssao = new PPScreenSpaceAmbientOcclusion(engine);
			engine->graphics->AddPostProcess(ssao);

			//engine->graphics->AddDefaultProcessTarget("ambientLight", ssao->GetAO());

			//ISound* sound = engine->librarys->CreateResource<ISound>();
			//sound->LoadFromFile(L"Data/Sound/beep.wav");

			//font = engine->librarys->CreateResource<IFont>();
			//font->Create(L"Arial", 16.0f);

			Scene::Initialize(args);
		}

		void SceneTim::Draw(const DrawArgs& args)
		{


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
			//light->PRS.Position = Vector3(
			//	sinf((float)args.Time.TotalTime / 5) * 50,
			//	0,
			//	cosf((float)args.Time.TotalTime / 5) * 50
			//);

			//elements[0]->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(args.Time.TotalTime, 0, 0);

			Scene::Update(args);
		}
	}
}
