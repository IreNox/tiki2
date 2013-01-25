
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
			: Scene(engine), timerExplo(1.0), explo(false)
		{

		}

		SceneMark::~SceneMark()
		{
            SafeRelease(&light);
            SafeRelease(&camera);
		}

		void SceneMark::Initialize(const InitializationArgs& args)
		{
			SceneGraph.Initialize(RectangleF::Create(0, 0, 512, 512), 3);

            GameObject* go = TIKI_NEW GameObject(engine);
			IMeshRenderer* renP = engine->librarys->CreateComponent<IMeshRenderer>(go);
			renP->SetMaterial(engine->content->LoadMaterial(L"os_default"));
			renP->GetMaterial()->TexDiffuse = engine->content->LoadTexture(L"checker");
			renP->SetMesh(engine->content->LoadMesh(L"rocket"));
			go->PRS.SPosition() = Vector3(5, 5, 5);
			this->AddElement(go);

			// Plane
			go = TIKI_NEW GameObject(engine);
            renP = engine->librarys->CreateComponent<IMeshRenderer>(go);
            renP->SetMaterial(engine->content->LoadMaterial(L"os_default"));
			renP->GetMaterial()->TexDiffuse = engine->content->LoadTexture(L"terrain/color_map1");
            renP->SetMesh(engine->content->LoadMesh(L"plane"));
            go->PRS.SPosition() = Vector3(0, -0.1f, 0);
            this->AddElement(go);
			
            // Light
            light = TIKI_NEW LightObject(engine);
            light->GetLight()->SetColor(Color(1, 1, 1, 1));
            light->GetLight()->SetRange(75.0f);
            light->PRS.SPosition() = Vector3(-5, 5, 1.5);
            light->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
            light->AddRef();
            this->AddElement(light);

            //cam
            camera = TIKI_NEW CameraObject(engine);			
            camera->PRS.SPosition() = Vector3(-1, 1.5f, 4.0f);
            camera->AddRef();
            (TIKI_NEW CameraFly(engine, camera));
            this->AddElement(camera);


            // --- Particles ---

			// HealAura
            go = TIKI_NEW GameObject(engine);
            go->PRS.SPosition() = Vector3(0, 1, 0);
            go->PRS.SScale() = Vector3(0.01f);
            auto heal = TIKI_NEW PEHealAura(engine);

            IParticleRenderer* healPR = engine->librarys->CreateComponent<IParticleRenderer>(go);
            healPR->SetTexture(engine->content->LoadTexture(L"particle/HealAura"));
            healPR->SetParticleEffect(heal);
            this->AddElement(go);

            // Fire
            fireEmitter = TIKI_NEW GameObject(engine);
            fireEmitter->PRS.SPosition() = Vector3(0, 0, 0);
            //fireEmitter->PRS.SScale() = Vector3(0.01f);

            fireEffect = TIKI_NEW PEFire(engine);
            fireEffect->SIsAlive(false);

            IParticleRenderer* firePR = engine->librarys->CreateComponent<IParticleRenderer>(fireEmitter);
            firePR->SetTexture(engine->content->LoadTexture(L"particle/fire"));
            firePR->SetParticleEffect(fireEffect);
            this->AddElement(fireEmitter);

			// Smoke
			smokeEmitter = TIKI_NEW GameObject(engine);
			smokeEmitter->PRS.SPosition() = Vector3(0, 0, 0);
			//smokeEmitter->PRS.SScale() = Vector3(0.01f);

			smokeEffect = TIKI_NEW PESmoke(engine);
			smokeEffect->SIsAlive(false);

			IParticleRenderer* smokePR = engine->librarys->CreateComponent<IParticleRenderer>(smokeEmitter);
			smokePR->SetTexture(engine->content->LoadTexture(L"particle/smoke"));
			smokePR->SetParticleEffect(smokeEffect);
			this->AddElement(smokeEmitter);


			// Explosion
			explosionEmitter = TIKI_NEW GameObject(engine);
			explosionEmitter->PRS.SPosition() = Vector3(0, 0, 0);
			//explosionEmitter->PRS.SScale() = Vector3(0.01f);
			expEffect = TIKI_NEW PEExplosion(engine);
            expEffect->SIsAlive(false);

			IParticleRenderer* explosionPR = engine->librarys->CreateComponent<IParticleRenderer>(explosionEmitter);
			explosionPR->SetTexture(engine->content->LoadTexture(L"particle/explosion")); // fix: explosion looks too crappy
			explosionPR->SetParticleEffect(expEffect);
			this->AddElement(explosionEmitter);


			// Blood
			bloodEmitter = TIKI_NEW GameObject(engine);
			bloodEmitter->PRS.SPosition() = Vector3(3, 2, 0);
			//bloodEmitter->PRS.SScale() = Vector3(0.01f);

			bloodEffect = TIKI_NEW PEBlood(engine);
			//bloodEffect->SIsAlive(false);

			IParticleRenderer* bloodPR = engine->librarys->CreateComponent<IParticleRenderer>(bloodEmitter);
			bloodPR->SetTexture(engine->content->LoadTexture(L"particle/Blood")); 
			bloodPR->SetParticleEffect(bloodEffect);
			this->AddElement(bloodEmitter);

			// Flash
			flashEmitter = TIKI_NEW GameObject(engine);
			flashEmitter->PRS.SPosition() = Vector3(-3, 1, 0);
			flashEmitter->PRS.SScale() = Vector3(0.01f);

			flashEffect = TIKI_NEW PEFlash(engine);
			//flashEffect->SIsAlive(false);

			IParticleRenderer* flashPR = engine->librarys->CreateComponent<IParticleRenderer>(flashEmitter);
			flashPR->SetTexture(engine->content->LoadTexture(L"particle/star")); 
			flashPR->SetParticleEffect(flashEffect);
			this->AddElement(flashEmitter);

			// Sparks
			sparksEmitter = TIKI_NEW GameObject(engine);
			sparksEmitter->PRS.SPosition() = Vector3(-6, 1, 0);

			sparksEffect = TIKI_NEW PESparks(engine);
			sparksEffect->SIsAlive(false);

			IParticleRenderer* sparksPR = engine->librarys->CreateComponent<IParticleRenderer>(sparksEmitter);
			sparksPR->SetTexture(engine->content->LoadTexture(L"particle/line_sparks")); 
			sparksPR->SetParticleEffect(sparksEffect);
			this->AddElement(sparksEmitter);


			// Shockwave
			shockwaveEmitter = TIKI_NEW GameObject(engine);
			shockwaveEmitter->PRS.SPosition() = Vector3(-6, 1, 0);

			shockwaveEffect = TIKI_NEW PEShockWave(engine);
			shockwaveEffect->SIsAlive(false);

			IParticleRenderer* shockPR = engine->librarys->CreateComponent<IParticleRenderer>(shockwaveEmitter);
			shockPR->SetTexture(engine->content->LoadTexture(L"particle/Shockwave")); 
			shockPR->SetParticleEffect(shockwaveEffect);
			this->AddElement(shockwaveEmitter);

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

			SceneGraph.GetAllGameObjects()[0]->PRS.SPosition() = Vector3(
				sinf((float)args.Time.TotalTime) * 7.5f,
				5,
				cosf((float)args.Time.TotalTime) * 7.5f
			);

			SceneGraph.GetAllGameObjects()[0]->PRS.SRotation() = Quaternion::CreateFromAxisAngle(
				Vector3::Normalize(Vector3(sinf((float)args.Time.TotalTime / 2), 0, cosf((float)args.Time.TotalTime / 2))),
				3.15149f
			);


			if (args.Input.GetKeyPressed(KEY_SPACE))
				expEffect->Trigger(
					1, expEffect->GParticleBudget(),
					Matrix::TransformCoordinate(
						Vector3(-0.8f, 0, 0),
						Matrix::Transpose(SceneGraph.GetAllGameObjects()[0]->PRS.GetWorld())
					) 
				);

			if (explo)
			{
				sparksEffect->Trigger(
					args.Time.ElapsedTime, 
					20,
					Matrix::TransformCoordinate(
					Vector3(0, 0, 0),
					Matrix::Transpose(sparksEmitter->PRS.GetWorld())
					)
					);

				explo = !timerExplo.IsReady(args.Time);
			}

 			if (args.Input.GetKeyPressed(KEY_N))
 			{

				shockwaveEffect->Trigger(1, shockwaveEffect->GParticleBudget(), 
					Matrix::TransformCoordinate(
					Vector3(0, 0, 0),
					Matrix::Transpose(shockwaveEmitter->PRS.GetWorld())
					)
				);

				sparksEffect->Trigger2(
					0, 
					Matrix::TransformCoordinate(
					Vector3(0, 0, 0),
					Matrix::Transpose(sparksEmitter->PRS.GetWorld())
					)
				);

				explo = true;
 			}


            fireEffect->Trigger(
                args.Time.ElapsedTime, 200,
                Matrix::TransformCoordinate(
                Vector3(0.8f, 0, 0),
                Matrix::Transpose(SceneGraph.GetAllGameObjects()[0]->PRS.GetWorld())
                ) 
            );


			smokeEffect->Trigger(
				args.Time.ElapsedTime, 200,
				Matrix::TransformCoordinate(
					Vector3(0.8f, 0, 0),
					Matrix::Transpose(SceneGraph.GetAllGameObjects()[0]->PRS.GetWorld())
				)
			);


			// Update base
			Scene::Update(args);
		}
	}
}
