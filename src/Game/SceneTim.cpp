
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
			
			MeshIndexed* mesh = (MeshIndexed*)engine->content->LoadMesh(L"Data/Resources/Models/Dice2.fbx");
			tex = engine->content->LoadTexture(L"Data/Resources/Textures/jumppad_diff.jpg");

			Material* mat = engine->content->LoadMaterial(L"Data\\Effects\\os_default.fx");
			mat->GetShader()->SetTexture("tex", tex);

			IMeshRenderer* render = engine->librarys->CreateComponent<IMeshRenderer>(go);
			render->SetMesh(mesh);
			render->SetMaterial(mat);
			mat->Release();
			mesh->Release();
			render->Release();

			IPhysicsMaterial* material = engine->librarys->CreateResource<IPhysicsMaterial>();
			material->SetRestitution(0.7f);
			material->SetDynamicFriction(0.7f);
			material->SetStaticFriction(0.5f);

			ITriangleMeshCollider* collider = engine->librarys->CreateComponent<ITriangleMeshCollider>(go);
			collider->SetMaterial(material->GetIndex());
			collider->SetCenter(Vector3(0, 3, -4));
			collider->SetDynamic(false);
			collider->SetGroup(CG_Collidable_Pushable);

			UInt32 count;
			UInt32* indexData;
			mesh->GetIndexData(&indexData, &count);
			collider->SetIndices(indexData, count);

			DefaultVertex* vertexData;
			mesh->GetVertexData((void**)&vertexData, &count);

			List<Vector3> list = List<Vector3>();
			UInt32 i = 0;
			count /= sizeof(DefaultVertex);
			while (i < count) { list.Add(Vector3(vertexData[i].Position)); i++; }

			Vector3* vectorData = list.ToArray();
			collider->SetVertices(vectorData, count);
			delete[](vectorData);

			this->AddElement(go);
			go->Release();

			light = new LightObject(engine);
			light->GetLight()->SetColor(Color(1, 1, 1, 1));
			light->GetLight()->SetRange(750.0f);
			light->PRS.SetPosition(Vector3(1500, 0, 0));
			this->AddElement(light);
			
			go = new CameraObject(engine);
			go->PRS.SetPosition(Vector3(0, 0, 5.0f));

			CameraFly* fly = new CameraFly(engine, go);
			fly->Release();

			this->AddElement(go);
			go->Release();

			go = new GameObject(engine);
			
			mat = engine->content->LoadMaterial(L"Data\\Effects\\os_cloddy.fx");
			mat->GetShader()->SetTexture("tex", tex);

			ITerrainRenderer* terrain = engine->librarys->CreateComponent<ITerrainRenderer>(go);
			terrain->LoadTerrain("Data/Cloddy/Datasets/terrain.E16C24.rect.dat", 8192, 2048);
			terrain->SetMaterial(mat);
			terrain->Release();
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

			engine->physics->DrawDebug();

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
