
#include "Game/SceneMark.h"

#include "Core/IPhysics.h"
#include "Core/LibraryManager.h"
#include "Core/IMeshRenderer.h"
#include "Core/IParticleRenderer.h"

#include "Game/CameraFly.h"

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
			IMeshRenderer* renP = engine->librarys->CreateComponent<IMeshRenderer>(go);
			renP->SetMaterial(engine->content->LoadMaterial(L"os_default"));
			renP->GetMaterial()->TexDiffuse = engine->content->LoadTexture(L"checker");
			renP->SetMesh(engine->content->LoadMesh(L"rocket"));
			go->PRS.SPosition() = Vector3(5, 5, 5);
			this->AddElement(go);

			// Plane
			go = new GameObject(engine);
            renP = engine->librarys->CreateComponent<IMeshRenderer>(go);
            renP->SetMaterial(engine->content->LoadMaterial(L"os_default"));
			renP->GetMaterial()->TexDiffuse = engine->content->LoadTexture(L"terrain/color_map1");
            renP->SetMesh(engine->content->LoadMesh(L"plane"));
            go->PRS.SPosition() = Vector3(0, -0.1f, 0);
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


            // --- Particles ---

			// HealAura
            go = new GameObject(engine);
            go->PRS.SPosition() = Vector3(0, 1, 0);
            go->PRS.SScale() = Vector3(0.01f);
            auto heal = new PEHealAura(engine);

            IParticleRenderer* healPR = engine->librarys->CreateComponent<IParticleRenderer>(go);
            healPR->SetTexture(engine->content->LoadTexture(L"particle/HealAura"));
            healPR->SetParticleEffect(heal);
            this->AddElement(go);

            // Fire
            fireEmitter = new GameObject(engine);
            fireEmitter->PRS.SPosition() = Vector3(0, 0, 0);
            //fireEmitter->PRS.SScale() = Vector3(0.01f);

            fireEffect = new PEFire(engine);
            fireEffect->SIsAlive(false);

            IParticleRenderer* firePR = engine->librarys->CreateComponent<IParticleRenderer>(fireEmitter);
            firePR->SetTexture(engine->content->LoadTexture(L"particle/fire"));
            firePR->SetParticleEffect(fireEffect);
            this->AddElement(fireEmitter);

			// Smoke
			smokeEmitter = new GameObject(engine);
			smokeEmitter->PRS.SPosition() = Vector3(0, 0, 0);
			smokeEmitter->PRS.SScale() = Vector3(0.01f);

			smokeEffect = new PESmoke(engine);
			smokeEffect->SIsAlive(false);

			IParticleRenderer* smokePR = engine->librarys->CreateComponent<IParticleRenderer>(smokeEmitter);
			smokePR->SetTexture(engine->content->LoadTexture(L"particle/smoke"));
			smokePR->SetParticleEffect(smokeEffect);
			this->AddElement(smokeEmitter);


			// Explosion
			explosionEmitter = new GameObject(engine);
			explosionEmitter->PRS.SPosition() = Vector3(0, 0, 0);
			explosionEmitter->PRS.SScale() = Vector3(0.01f);
			expEffect = new PEExplosion(engine);
            expEffect->SIsAlive(false);

			IParticleRenderer* explosionPR = engine->librarys->CreateComponent<IParticleRenderer>(explosionEmitter);
			explosionPR->SetTexture(engine->content->LoadTexture(L"particle/fire")); // fix: explosion looks too crappy
			explosionPR->SetParticleEffect(expEffect);
			this->AddElement(explosionEmitter);


			// Blood
			bloodEmitter = new GameObject(engine);
			bloodEmitter->PRS.SPosition() = Vector3(3, 2, 0);
			//bloodEmitter->PRS.SScale() = Vector3(0.01f);

			bloodEffect = new PEBlood(engine);
			//bloodEffect->SIsAlive(false);

			IParticleRenderer* bloodPR = engine->librarys->CreateComponent<IParticleRenderer>(bloodEmitter);
			bloodPR->SetTexture(engine->content->LoadTexture(L"particle/Blood")); 
			bloodPR->SetParticleEffect(bloodEffect);
			this->AddElement(bloodEmitter);


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
			if (args.Input.GetKey(KEY_J))
				smokeEmitter->PRS.SPosition() = smokeEmitter->PRS.GPosition() + Vector3(0.01f, 0, 0);
			else if (args.Input.GetKey(KEY_L))
				smokeEmitter->PRS.SPosition() = smokeEmitter->PRS.GPosition() - Vector3(0.01f, 0, 0);

			elements[0]->PRS.SPosition() = Vector3(
				sinf((float)args.Time.TotalTime) * 7.5f,
				5,
				cosf((float)args.Time.TotalTime) * 7.5f
			);

			elements[0]->PRS.SRotation() = Quaternion::CreateFromAxisAngle(
				Vector3::Normalize(Vector3(sinf((float)args.Time.TotalTime / 2), 0, cosf((float)args.Time.TotalTime / 2))),
				3.15149f
			);


            if (args.Input.GetKeyPressed(KEY_SPACE))
                expEffect->Trigger(
                    (UInt32)(200 * args.Time.ElapsedTime),
                    Vector3::TransformCoordinate(
                    Vector3(-0.8f, 0, 0),
                    Matrix::Transpose(elements[0]->PRS.GetWorld())
                    ) * 100
                );


            fireEffect->Trigger(
                (UInt32)(200 * args.Time.ElapsedTime),
                //Vector3(0,5,0)
                Vector3::TransformCoordinate(
                Vector3(0.8f, 0, 0),
                Matrix::Transpose(elements[0]->PRS.GetWorld())
                ) * 100.0f
                );


			smokeEffect->Trigger(
				(UInt32)(200 * args.Time.ElapsedTime),
				//Vector3(0,5,0)
				Vector3::TransformCoordinate(
					Vector3(0.8f, 0, 0),
					Matrix::Transpose(elements[0]->PRS.GetWorld())
				) * 100.0f
			);

			// Update base
			Scene::Update(args);
		}
	}
}
