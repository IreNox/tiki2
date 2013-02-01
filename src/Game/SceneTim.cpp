
#include "Game/SceneTim.h"

#include "Core/Engine.h"
#include "Core/IPhysics.h"
#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"
#include "Core/ISoundSystem.h"
#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Core/IMeshRenderer.h"
#include "Core/IParticleRenderer.h"
#include "Core/IPhysicsMaterial.h"
#include "Core/ISound.h"

#include "Core/Mesh.h"
#include "Core/DefaultVertex.h"

#include "Game/CameraFly.h"
#include "Game/CameraTPS.h"

#include "Game/PEShootMG.h"

#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Scripts;
		using namespace TikiEngine::Vertices;

		SceneTim::SceneTim(Engine* engine)
			: Scene(engine), showRenderTargets(false)
		{
		}

		SceneTim::~SceneTim()
		{
			SafeRelease(&tex1);
			SafeRelease(&tex2);

			SafeRelease(&light);
			SafeRelease(&camera);
			//SafeRelease(&font);
		}

		void SceneTim::Initialize(const InitializationArgs& args)
		{
			SceneGraph.Initialize(RectangleF::Create(-512,-512,1024,1024),3);

			tex1 = engine->content->LoadTexture(L"logo");
			tex2 = engine->content->LoadTexture(L"checker");

			// Building
			GameObject* go = TIKI_NEW GameObject(engine);
			go->SModel(engine->content->LoadModel(L"mainbuilding"));
			go->PRS.SScale() = 0.01f;
			go->PRS.SPosition() = Vector3(0, 0, 0);
			this->AddElement(go);

			// Plane
			go = TIKI_NEW GameObject(engine);
			auto renP = engine->librarys->CreateComponent<IMeshRenderer>(go);
			renP->SetMaterial(engine->content->LoadMaterial(L"os_default"));
			renP->GetMaterial()->TexDiffuse = engine->content->LoadTexture(L"terrain/color_map1");
			renP->SetMesh(engine->content->LoadMesh(L"plane"));
			go->PRS.SPosition() = Vector3(0, -0.1f, 0);
			this->AddElement(go);

			//// Marine
			//go = TIKI_NEW GameObject(engine);
			//go->SModel(engine->content->LoadModel(L"unit_marine"));
			//go->GModel()->GetMesh("heavyPlasma")->SetVisible(false);
			//go->PRS.SScale() = 0.01f;
			//go->PRS.SPosition() = Vector3(15, 0, 0);
			//this->AddElement(go);

			light = TIKI_NEW LightObject(engine);
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(75.0f);
			light->PRS.SPosition() = Vector3(-10, 10, 2.5);
			light->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
			light->AddRef();
			this->AddElement(light);

			camera = TIKI_NEW CameraObject(engine);			
			camera->PRS.SPosition() = Vector3(-1, 1.5f, 4.0f);
			camera->AddRef();
			(TIKI_NEW CameraFly(engine, camera));
			this->AddElement(camera);

			//font = engine->librarys->CreateResource<IFont>();
			//font->Create(L"Arial", 14.0f);
			//font->AddRef();
			
			Scene::Initialize(args);
		}

		#pragma region Member - Draw
		void SceneTim::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);

			//engine->sprites->Draw(
			//	tex1,
			//	Rectangle(10, 10, 512, 512)
			//);

			//engine->sprites->Draw(
			//	tex2,
			//	Rectangle(266, 266, 512, 512)
			//);
			
			if (showRenderTargets)
			{
				engine->sprites->Draw(
					engine->graphics->GetNormalTarget(),
					Rectangle(10, 10, 200, 180)
				);

				engine->sprites->Draw(
					engine->graphics->GetLightTarget(),
					Rectangle(10, 200, 200, 180)
				);

				engine->sprites->Draw(
					engine->graphics->GetScreenTarget(),
					Rectangle(10, 390, 200, 180)
				);
			}
			
			#if _DEBUG
			//engine->physics->DrawDebug();
			#endif
		}
		#pragma endregion

		#pragma region Member - Update
		void SceneTim::Update(const UpdateArgs& args)
		{			
			if (args.Input.GetKeyReleased(KEY_F3))
				showRenderTargets = !showRenderTargets;

			Vector3 move = Vector3(
				(args.Input.GetKey(KEY_F) ? -1.0f : 0.0f) + (args.Input.GetKey(KEY_H) ? 1.0f : 0.0f),
				(args.Input.GetKey(KEY_Z) ? -1.0f : 0.0f) + (args.Input.GetKey(KEY_R) ? 1.0f : 0.0f),
				(args.Input.GetKey(KEY_G) ? -1.0f : 0.0f) + (args.Input.GetKey(KEY_T) ? 1.0f : 0.0f)
			) * (float)(args.Time.ElapsedTime * 10.0);

			light->PRS.SPosition() += move;

			Scene::Update(args);
		}
		#pragma endregion
	}
}
