
#include "Game/SceneAdrian.h"

#include "Core/IMeshRenderer.h"
#include "Core/LibraryManager.h"

#include "Core/MeshIndexed.h"

#include "Core/DefaultVertex.h"

#include "Core/CameraObject.h"

#include "Core/IContentManager.h"

#include "Game/CameraFly.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Scripts;
		using namespace TikiEngine::Objects;
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Components;

		SceneAdrian::SceneAdrian(Engine* engine)
			: Scene(engine)
		{
		}

		SceneAdrian::~SceneAdrian()
		{
		}

		void SceneAdrian::Initialize(const InitializationArgs& args)
		{

			GameObject* go = new GameObject(engine);

			Mesh* mesh = engine->content->LoadMesh(L"Data/Resources/Models/humanoid.fbx");
		
			ITexture* tex = engine->content->LoadTexture(L"Data/Resources/Textures/checker.png");

			Material* mat = engine->content->LoadMaterial(L"Data//Effects//os_default.fx");
			mat->GetShader()->SetTexture("tex", tex);

			IMeshRenderer* render = engine->librarys->CreateComponent<IMeshRenderer>(go);
			render->SetMesh(mesh);
			render->SetMaterial(mat);

			mat->Release();
			mesh->Release();
			render->Release();

			this->AddElement(go);
			go->Release();

			go = new CameraObject(engine);
			go->PRS.Position.Z = 70.0f;
			go->PRS.Position.Y = 40.0f;

			CameraFly* fly = new CameraFly(engine, go);
			fly->Release();

			this->AddElement(go);
			go->Release();

			Scene::Initialize(args);
		}

		void SceneAdrian::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);
		}

		void SceneAdrian::Update(const UpdateArgs& args)
		{
			Scene::Update(args);
		}
	}
}
