
#include "Game/SceneMark.h"


#include "Core/IPhysics.h"
#include "Core/LibraryManager.h"
#include "Core/IMeshRenderer.h"
#include "Core/IParticleRenderer.h"


#include "Game/CameraFly.h"
#include "Game/PEHealAura.h"

namespace TikiEngine
{
	namespace Game
	{
        using namespace TikiEngine::Scripts;

		SceneMark::SceneMark(Engine* engine)
			: Scene(engine)
		{

		}

		SceneMark::~SceneMark()
		{
            SafeRelease(&light);
            SafeRelease(&camera);
		}

		void SceneMark::Initialize(const InitializationArgs& args)
		{
            GameObject* go = new GameObject(engine);
            auto renP = engine->librarys->CreateComponent<IMeshRenderer>(go);

            Material* mat = engine->content->LoadMaterial(L"os_default");
            mat->TexDiffuse		= engine->content->LoadTexture(L"terrain/color_map1");
            renP->SetMaterial(mat);
            renP->SetMesh(engine->content->LoadMesh(L"plane"));
            go->PRS.SPosition() = Vector3(0, -0.1f, 0);
            //go->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(0, 3.14159f, 0);
            //go->PRS.SScale() = Vector3(1, 1, -1);
            this->AddElement(go);


            // Light
            light = new LightObject(engine);
            light->GetLight()->SetColor(Color(1, 1, 1, 1));
            light->GetLight()->SetRange(75.0f);
            light->PRS.SPosition() = Vector3(-5, 5, 1.5);
            light->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
            light->AddRef();
            this->AddElement(light);

            //cam
            camera = new CameraObject(engine);			
            camera->PRS.SPosition() = Vector3(-1, 1.5f, 4.0f);
            camera->AddRef();
            (new CameraFly(engine, camera));
            this->AddElement(camera);


            // particles
            go = new GameObject(engine);
            go->PRS.SPosition() = Vector3(0, 1, 0);
            go->PRS.SScale() = Vector3(0.01f);
            auto behavior = new PEHealAura(engine);

            IParticleRenderer* effect = engine->librarys->CreateComponent<IParticleRenderer>(go);
            effect->SetTexture(engine->content->LoadTexture(L"particle/HealAura"));
            effect->SetParticleEffect(behavior);
            this->AddElement(go);



			Scene::Initialize(args);
		}

		void SceneMark::Draw(const DrawArgs& args)
		{

			#if _DEBUG
			//engine->physics->DrawDebug();
			#endif




			Scene::Draw(args);
		}

		void SceneMark::Update(const UpdateArgs& args)
		{

			// Update base
			Scene::Update(args);
		}
	}
}
