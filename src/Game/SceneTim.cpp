
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
#include "Core/ITriangleMeshCollider.h"
#include "Core/ISound.h"

#include "Core/MeshIndexed.h"
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
		using namespace TikiEngine::Components;

		SceneTim::SceneTim(Engine* engine)
			: Scene(engine)
		{
		}

		SceneTim::~SceneTim()
		{
			SafeRelease(&tex);
			//SafeRelease(&ssao);
			SafeRelease(&light);
			SafeRelease(&font);
		}

		void SceneTim::Initialize(const InitializationArgs& args)
		{
			GameObject* go = new GameObject(engine);
			
			go->Model = engine->content->LoadModel(L"bridge");
			tex = engine->content->LoadTexture(L"checker");

			Material* mat = engine->content->LoadMaterial(L"os_default");
			mat->GetShader()->SetTexture("tex", tex);

			go->Model->SetMaterial(mat);
			mat->Release();

			this->AddElement(go);
			go->Release();

			light = new LightObject(engine);
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(750.0f);
			light->PRS.Rotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
			this->AddElement(light);
			
			go = new CameraObject(engine);
			go->PRS.Position() = Vector3(0, 0, 5.0f);

			CameraFly* fly = new CameraFly(engine, go);
			fly->Release();

			this->AddElement(go);
			go->Release();

			//// Cloddy
			//go = new GameObject(engine);
			//
			//mat = engine->content->LoadMaterial(L"os_cloddy");
			//mat->GetShader()->SetTexture("tex", tex);

			//ITerrainRenderer* terrain = engine->librarys->CreateComponent<ITerrainRenderer>(go);
			//terrain->LoadTerrain("Data/Cloddy/Datasets/terrain.E16C24.rect.dat", 8192, 2048);
			//terrain->SetMaterial(mat);
			//terrain->Release();
			//mat->Release();

			//this->AddElement(go);
			//go->Release();

			//// Blur
			//engine->graphics->AddPostProcess(new PPBlur(engine));

			//// SSAO
			//ssao = new PPScreenSpaceAmbientOcclusion(engine);
			//engine->graphics->AddPostProcess(ssao);
			//engine->graphics->AddDefaultProcessTarget("ambientLight", ssao->GetAO());

			//// Sound
			//ISound* sound = engine->librarys->CreateResource<ISound>();
			//sound->LoadFromFile(L"beep");

			font = engine->librarys->CreateResource<IFont>();
			font->Create(L"Arial", 14.0f);

			GUIControl::SetDefaultFont(font);

			button = new GUIButton(engine);
			button->Position() = Vector2(500, 500);
			button->Size() = Vector2(512, 128);

			Scene::Initialize(args);
		}

		void SceneTim::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);

			tmp = Vector3(
				 args.Update.Input.MousePositionDisplay.X,
				 args.Update.Input.MousePositionDisplay.Y,
				 args.Update.Input.MousePositionDisplay.X
			);

			wostringstream s;
			s << "Light: X: " << tmp.X << ", Y:"  << tmp.Y << ", Z:" << tmp.Z;

			engine->sprites->DrawString(font, s.str(), Vector2(10, 600));

			engine->sprites->Draw(
				engine->graphics->GetDepthTarget(),
				Rectangle(10, 10, 200, 180)
			);

			engine->sprites->Draw(
				engine->graphics->GetNormalTarget(),
				Rectangle(10, 200, 200, 180)
			);

			//engine->sprites->Draw(
			//	ssao->GetAO(),
			//	Rectangle(10, 390, 200, 180)
			//);

			engine->physics->DrawDebug();

			/*engine->sprites->Draw(
				tex,
				Vector2(300, 300),
				args.Time.TotalTime,
				Vector2(256, 256),
				Vector2(1),
				1
			);*/

			button->Draw(args);
		}

		void SceneTim::Update(const UpdateArgs& args)
		{
			//// light settings test
			//Vector3 move = Vector3(
			//	(args.Input.GetKey(KEY_L) ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_J) ? -1.0f : 0.0f),
			//	(args.Input.GetKey(KEY_I)   ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_K) ?  -1.0f : 0.0f),
			//	(args.Input.GetKey(KEY_O)   ? 1.0f : 0.0f) + (args.Input.GetKey(KEY_U) ?  -1.0f : 0.0f)
			//) * args.Time.ElapsedTime;

			//// tmp = class var
			//tmp += move;

			//light->PRS.SetRotation(
			//	Quaternion::CreateFromYawPitchRoll(tmp.X, tmp.Y, tmp.Z)
			//);


			//elements[0]->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(args.Time.TotalTime, 0, 0);

			if (args.Input.GetKey(KEY_F12))
			{
				engine->graphics->MakeScreenshot();
			}

			button->Update(args);

			Scene::Update(args);
		}
	}
}
