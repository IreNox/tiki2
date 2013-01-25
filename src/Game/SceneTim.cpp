
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
			: Scene(engine), showRenderTargets(true)
		{
		}

		SceneTim::~SceneTim()
		{
			//SafeRelease(&tex);
			SafeRelease(&light);
			SafeRelease(&camera);

			SafeRelease(&font);
		}

		void SceneTim::Initialize(const InitializationArgs& args)
		{
			SceneGraph.Initialize(RectangleF::Create(-512,-512,1024,1024),3);

			GameObject* go = TIKI_NEW GameObject(engine);
			go->SModel(engine->content->LoadModel(L"mainbuilding"));
			go->PRS.SScale() = 0.01f;
			go->PRS.SPosition() = Vector3(0, 0, 0);

			this->AddElement(go);

			//go = TIKI_NEW GameObject(engine);
			//go->SModel(engine->content->LoadModel(L"marine_l"));
			//go->PRS.SScale() = 0.01f;
			//go->PRS.SPosition() = Vector3(3, 0, 3);

			//this->AddElement(go);

			//go = TIKI_NEW GameObject(engine);
			//go->SModel(engine->content->LoadModel(L"marine_l"));
			//go->PRS.SScale() = 0.01f;
			//go->PRS.SPosition() = Vector3(-3, 0, -3);

			//this->AddElement(go);

			//dof = TIKI_NEW PPDepthOfField(engine);
			//engine->graphics->AddPostProcess(dof);


			/////////////////
			//Particle Effect
			//GameObject* go = TIKI_NEW GameObject(engine);

			// auto behavior = TIKI_NEW PEShootMG(engine);

			//IParticleRenderer* effect = engine->librarys->CreateComponent<IParticleRenderer>(go);
			//effect->SetTexture(engine->content->LoadTexture(L"particle/mg"));
			//effect->SetParticleEffect(behavior);

			//this->AddElement(go);

			////////
			// Model
			//for (int i = -1000; i < 1000; i++)
			//{
			//	GameObject* go = TIKI_NEW GameObject(engine);

			//	if (i == 0)
			//	{
			//		go->SModel(args.Content->LoadModel(L"mark"));
			//	}
			//	else
			//	{
			//		go->SModel(args.Content->LoadModel(L"soldier"));
			//	}
			//	go->PRS.SScale() = Vector3(0.01f);
			//	go->PRS.SPosition().X = i * 2;

			//	this->AddElement(go);
			//}

			//target = engine->librarys->CreateResource<IRenderTarget>();
			//target->CreateScreenSize();

			//GameObject* go = TIKI_NEW GameObject(engine);

			//go->SModel(args.Content->LoadModel(L"marine_l"));
			//go->GModel()->SetAnimation(0);

			//renB = engine->librarys->CreateComponent<IMeshRenderer>(go);

			//Material* mat = engine->content->LoadMaterial(L"os_default");
			//mat->TexDiffuse		= engine->content->LoadTexture(L"building03_05/building03_05_Diff");
			//mat->TexNormalMap	= engine->content->LoadTexture(L"building03_05/building03_05_Normal");
			//mat->TexSpecularMap	= engine->content->LoadTexture(L"building03_05/building03_05_Spec");
			//renB->SetMaterial(mat);
			//renB->SetMesh(engine->content->LoadMesh(L"marine_l"));

			//go->PRS.SScale() = Vector3(0.02f);
			//this->AddElement(go);


			go = TIKI_NEW GameObject(engine);
			auto renP = engine->librarys->CreateComponent<IMeshRenderer>(go);

			Material* mat = engine->content->LoadMaterial(L"os_default");
			mat->TexDiffuse		= engine->content->LoadTexture(L"terrain/color_map1");
			renP->SetMaterial(mat);
			renP->SetMesh(engine->content->LoadMesh(L"plane"));
			go->PRS.SPosition() = Vector3(0, -0.1f, 0);
			this->AddElement(go);

			//RenderTarget
			//targetLight = engine->librarys->CreateResource<IRenderTarget>();
			//targetLight->CreateScreenSize();
			//targetLight->AddRef();

			// Light
			light = TIKI_NEW LightObject(engine);
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(75.0f);
			light->PRS.SPosition() = Vector3(-5, 5, 1.5);
			light->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
			light->AddRef();

			this->AddElement(light);
			
			// Camera
			//cameraLight = TIKI_NEW CameraObject(engine);			
			//cameraLight->PRS.SPosition() = light->PRS.GPosition();
			//cameraLight->PRS.SRotation() = light->PRS.GRotation();
			//cameraLight->GetCameraComponent()->SetRenderTarget(targetLight);
			//cameraLight->AddRef();

			//this->AddElement(cameraLight);

			camera = TIKI_NEW CameraObject(engine);			
			camera->PRS.SPosition() = Vector3(-1, 1.5f, 4.0f);
			camera->AddRef();
			(TIKI_NEW CameraFly(engine, camera));
			this->AddElement(camera);

			// SSAO
			//ssao = TIKI_NEW PPScreenSpaceAmbientOcclusion(engine);
			//engine->graphics->AddPostProcess(ssao);
			//engine->graphics->AddDefaultProcessTarget("ambientLight", ssao->GetAO());

			//auto blur = TIKI_NEW PPBlur(engine);
			//blur->GetPasses()[0]->SetInput("tex", engine->graphics->GetLightTarget());
			//blur->GetPasses()[1]->SetOutput(0, engine->graphics->GetLightTarget());
			//engine->graphics->AddPostProcess(blur);

			font = engine->librarys->CreateResource<IFont>();
			font->Create(L"Arial", 14.0f);
			font->AddRef();
			
			Scene::Initialize(args);
		}

		#pragma region Member - Draw
		void SceneTim::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);

			if (showRenderTargets)
			{
				engine->sprites->Draw(
					engine->graphics->GetNormalTarget(),
					Rectangle(500, 10, 200, 180)
				);

				engine->sprites->Draw(
					engine->graphics->GetLightTarget(),
					Rectangle(500, 200, 200, 180)
				);

				engine->sprites->Draw(
					engine->graphics->GetScreenTarget(),
					Rectangle(500, 390, 200, 180)
				);
			}
			
			//Vector2 mouse = Vector2(1.1f - args.Update.Input.MousePosition.X + 0.1f, 1.1f - args.Update.Input.MousePosition.Y + 0.1f);
			//Vector2 rot = Vector2(0.3f * mouse.X, 0.4f * mouse.Y);

			//3D Interface
			//engine->sprites->Draw3D(
			//	engine->content->LoadTexture(L"hud/circle_main_0"),
			//	Matrix::Identity,
			//	Matrix::CreateScaleMatrix(1536) * Matrix::CreateFromYawPitchRollRadians(rot.X, rot.Y, (float)args.Time.TotalTime / 8) * Matrix::CreateTranslation(200.0f, -200.0f, -200.0f)
			//);

			//engine->sprites->Draw3D(
			//	engine->content->LoadTexture(L"hud/circle_main_1"),
			//	Matrix::Identity,
			//	Matrix::CreateScaleMatrix(1536) * Matrix::CreateFromYawPitchRollRadians(rot.X, rot.Y, (float)args.Time.TotalTime / -5) * Matrix::CreateTranslation(200.0f, -200.0f, -200.0f)
			//);

			#if _DEBUG
			//engine->physics->DrawDebug();
			#endif
		}
		#pragma endregion

		#pragma region Member - Update
		void SceneTim::Update(const UpdateArgs& args)
		{			
			//float b = (float)args.Time.TotalTime / 4.0f;
			//b = fmodf(b, 6.28318f);

			//Matrix vp = this->GetMainCamera()->WorldToScreen();
			//Vector3 pos = this->SceneGraph.GetAllGameObjects()[1]->PRS.GPosition();
			//
			//Vector4 pos2 = Matrix::Transform(
			//	Vector4(pos.X, pos.Y, pos.Z, 1.0f),
			//	vp
			//);

			if (args.Input.GetKeyReleased(KEY_F3)) showRenderTargets = !showRenderTargets;

			//dof->GetPasses()[0]->GetShader()->SetVector4("value", pos2);

			//this->SceneGraph.GetDefaultGOs()[0]->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(b, 0, 0);
			//this->SceneGraph.GetDefaultGOs()[0]->GModel()->GetMesh("tower")->SetLocalMatrix(Matrix::CreateFromYawPitchRollRadians(b, 0, 0));
			//elements[0]->GModel()->GetMesh("MG")->SetLocalMatrix(Matrix::CreateFromAxisAngle(Vector3::Up, b));

			//Vector3 move = Vector3(
			//	(args.Input.GetKey(KEY_L) ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_J) ? -1.0f : 0.0f),
			//	(args.Input.GetKey(KEY_I) ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_K) ? -1.0f : 0.0f),
			//	(args.Input.GetKey(KEY_O) ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_U) ? -1.0f : 0.0f)
			//) * (float)args.Time.ElapsedTime;

			//tmp += move;

			//light->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(tmp.X, tmp.Y, tmp.Z);

			//if (args.Input.GetKey(KEY_F12))
			//{
			//	engine->graphics->MakeScreenshot();
			//}

			Scene::Update(args);
		}
		#pragma endregion
	}
}
