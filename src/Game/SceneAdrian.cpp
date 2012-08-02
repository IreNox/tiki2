
#include "Game/SceneAdrian.h"

#include "Core/IMeshRenderer.h"
#include "Core/LibraryManager.h"

#include "Core/MeshIndexed.h"

#include "Core/DefaultVertex.h"

#include "Core/CameraObject.h"

#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Game
	{
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
			CameraObject* co = new CameraObject(engine);
			this->AddElement(co);

			Mesh *mesh = engine->content->LoadFbxMesh(L"Data\\Resources\\Dice2.fbx");

			if(mesh != 0)
			{
				delete(mesh);
				mesh = 0;
			}

			Scene::Initialize(args);

			mainCamera = co->GetCameraComponent();
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
