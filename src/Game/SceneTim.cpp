
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

#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Scripts;
		using namespace TikiEngine::Vertices;

		SceneTim::SceneTim(Engine* engine)
			: Scene(engine) //, lastTime(0), dynamicBox(0)
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
			///////////////////
			////Particle Effect
			//GameObject* go = new GameObject(engine);

			//behavior = new ParticleTest(engine);

			//IParticleRenderer* effect = engine->librarys->CreateComponent<IParticleRenderer>(go);
			//effect->SetTexture(engine->content->LoadTexture(L"particle/mg"));
			//effect->SetParticleEffect(behavior);

			//this->AddElement(go);

			//////////
			////Cloddy
			//go = new GameObject(engine);
			//Material* mat = engine->content->LoadMaterial(L"os_cloddy");
			//ITerrainRenderer* terrain = engine->librarys->CreateComponent<ITerrainRenderer>(go);
			//terrain->LoadTerrain("Data/Cloddy/Datasets/pitch.E16C24.rect.dat", 8192, 512);
			//terrain->SetMaterial(mat);

			//this->AddElement(go);

			////////
			// Model
			//for (int i = -1000; i < 1000; i++)
			//{
			//	GameObject* go = new GameObject(engine);

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

			GameObject* go = new GameObject(engine);

			go->SModel(args.Content->LoadModel(L"marine_l"));

			//IMeshRenderer* render = engine->librarys->CreateComponent<IMeshRenderer>(go);

			//Material* mat = engine->content->LoadMaterial(L"os_default");
			//mat->TexDiffuse   = engine->content->LoadTexture(L"building_03/building_03_Diff");
			//mat->TexNormalMap = engine->content->LoadTexture(L"building_03/building_03_Normal");
			////mat->TexSpecular = engine->content->LoadTexture(L"building_03/building_03_Spec");
			//render->SetMaterial(mat);
			//render->SetMesh(engine->content->LoadMesh(L"test"));

			go->PRS.SScale() = Vector3(0.01f);

			this->AddElement(go);

			//RenderTarget
			//targetLight = engine->librarys->CreateResource<IRenderTarget>();
			//targetLight->CreateScreenSize();
			//targetLight->AddRef();

			// Light
			light = new LightObject(engine);
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(75.0f);
			light->PRS.SPosition() = Vector3(-5, 5, 1.5);
			light->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
			light->AddRef();

			this->AddElement(light);
			
			// Camera
			//cameraLight = new CameraObject(engine);			
			//cameraLight->PRS.SPosition() = light->PRS.GPosition();
			//cameraLight->PRS.SRotation() = light->PRS.GRotation();
			//cameraLight->GetCameraComponent()->SetRenderTarget(targetLight);
			//cameraLight->AddRef();

			//this->AddElement(cameraLight);

			camera = new CameraObject(engine);			
			camera->PRS.SPosition() = Vector3(0, 0, 5.0f);
			camera->AddRef();
			(new CameraFly(engine, camera));
			this->AddElement(camera);

			// SSAO
			ssao = new PPScreenSpaceAmbientOcclusion(engine);
			engine->graphics->AddPostProcess(ssao);
			//engine->graphics->AddDefaultProcessTarget("ambientLight", ssao->GetAO());

			//auto blur = new PPBlur(engine);
			//blur->GetPasses()[0]->SetInput("tex", ssao->GetAO());
			//blur->GetPasses()[1]->SetOutput(0, ssao->GetAO());
			//engine->graphics->AddPostProcess(blur);

			#pragma region Old Stuff
			//IPhysicsMaterial* material; 
			////material = engine->content->LoadPhysicsMaterial(L"TODO");
			//material = engine->librarys->CreateResource<IPhysicsMaterial>();
			//material->SetRestitution(0.2f);
			//material->SetDynamicFriction(0.7f);
			//material->SetStaticFriction(0.5f); // static friction may be higher than 1.

			// Cloddy
			//go = new GameObject(engine);

			//mat = engine->content->LoadMaterial(L"os_cloddy");
			//mat->GetShader()->SetTexture("tex", tex);

			//terrain = engine->librarys->CreateComponent<ITerrainRenderer>(go);
			//terrain->LoadTerrain("Data/Cloddy/Datasets/terrain.E16C24.rect.dat", 8192, 2048);
			//terrain->SetMaterial(mat);
			//terrain->Release();
			//mat->Release();

			//collider = engine->librarys->CreateComponent<ITriangleMeshCollider>(go);
			//collider->SetMaterial(material->GetIndex());
			//collider->SetCenter(Vector3::Zero);
			//collider->SetDynamic(false);

			//this->AddElement(go);
			//go->Release();

			//go = new GameObject(engine);
			//go->Model = engine->content->LoadModel(L"replaceme_cube");
			//go->Model->SetMaterial(mat);
			//dynamicBox = engine->librarys->CreateComponent<IBoxCollider>(go);
			//dynamicBox->SetMaterial(material->GetIndex()); // 0 = default material	
			//dynamicBox->SetCenter(Vector3(0, 20, 0));
			//dynamicBox->SetSize(Vector3(1, 1, 1));
			//dynamicBox->SetDynamic(true);
			//// assign collision groups after object is created, else it won't work!
			//dynamicBox->SetGroup(CG_Collidable_Pushable);
			//this->AddElement(go);
			//go->Release();

			//// Blur
			//engine->graphics->AddPostProcess(new PPBlur(engine));

			//// Sound
			//ISound* sound = engine->librarys->CreateResource<ISound>();
			//sound->LoadFromFile(L"beep");
			#pragma endregion

			font = engine->librarys->CreateResource<IFont>();
			font->Create(L"Arial", 14.0f);
			font->AddRef();
			
			Scene::Initialize(args);
		}

		#pragma region Member - Draw
		void SceneTim::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);

			//Vector3 tmp = Vector3((float*)camera->PRS.GRotation().arr);

			//wostringstream s;
			//s << "Time: " << args.Time.TotalTime;
			//engine->sprites->DrawString(font, s.str(), Vector2(10, 600));

			engine->sprites->Draw(
				ssao->GetAO(),
				Rectangle(10, 10, 200, 180)
			);

			engine->sprites->Draw(
				engine->graphics->GetNormalTarget(),
				Rectangle(10, 200, 200, 180)
			);

			//engine->sprites->Draw(
			//	targetLight,
			//	Rectangle(10, 390, 200, 180)
			//);

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

			/*engine->sprites->Draw(
				tex,
				Vector2(300, 300),
				args.Time.TotalTime,
				Vector2(256, 256),
				Vector2(1),
				1
			);*/
		}
		#pragma endregion

		#pragma region Member - Update
		void SceneTim::Update(const UpdateArgs& args)
		{
			//elements[0]->PRS.SPosition() = Vector3(
			//	sin(args.Time.TotalTime) * 3,
			//	0,
			//	cos(args.Time.TotalTime) * 3
			//);

			//if (args.Input.GetKeyPressed(KEY_F5))
			//{
			//	if (elements[0]->GetComponent<IMeshRenderer>()->GetMaterial()->TexNormalMap != 0)
			//	{
			//		elements[0]->GetComponent<IMeshRenderer>()->GetMaterial()->TexNormalMap = 0;
			//	}
			//	else
			//	{
			//		elements[0]->GetComponent<IMeshRenderer>()->GetMaterial()->TexNormalMap = engine->content->LoadTexture(L"building_03/building_03_Normal");
			//	}
			//}

			//// light settings test
			//Vector3 move = Vector3(
			//	(args.Input.GetKey(KEY_L) ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_J) ? -1.0f : 0.0f),
			//	(args.Input.GetKey(KEY_I)   ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_K) ?  -1.0f : 0.0f),
			//	(args.Input.GetKey(KEY_O)   ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_U) ?  -1.0f : 0.0f)
			//) * args.Time.ElapsedTime;

			//// tmp = class var
			//if (dynamicBox)
			//{
			//	tmp = dynamicBox->GetGameObject()->PRS.GPosition();
			//}

			//tmp.Z = terrain->SampleHeight(tmp);

			//light->PRS.SetRotation(
			//	Quaternion::CreateFromYawPitchRoll(tmp.X, tmp.Y, tmp.Z)
			//);


			//elements[0]->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(args.Time.TotalTime, 0, 0);

			/*if (args.Input.GetKeyPressed(KEY_F5))
			{
				dynamicBox->SetCenter(Vector3(0, 30, 0));
			}

			if (args.Input.GetKeyPressed(KEY_F6))
			{
				dynamicBox->SetCenter(camera->PRS.GPosition());
				dynamicBox->GetRigidBody()->SetVelocity(camera->PRS.GetForward() * 20);
			}

			if (args.Time.TotalTime - lastTime > 0.1f)
			{
				List<GameObject*> list = List<GameObject*>();
				list.Add(dynamicBox->GetGameObject());

				terrain->UpdateCollider(collider, &list);
				lastTime = args.Time.TotalTime;
			}*/

			//if (args.Input.GetKey(KEY_F12))
			//{
			//	engine->graphics->MakeScreenshot();
			//}

			Scene::Update(args);
		}
		#pragma endregion
	}
}
