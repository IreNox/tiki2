
#include "Game/SceneAdrian.h"

namespace TikiEngine
{
	namespace Game
	{
		SceneAdrian::SceneAdrian(Engine* engine)
			: Scene(engine)
		{
		}

		SceneAdrian::~SceneAdrian()
		{
		}

		void SceneAdrian::Initialize(const InitializationArgs& args)
		{
			Mesh *mesh = engine->content->LoadFbxMesh(L"Data\\Resources\\Dice2.fbx");

			if(mesh != 0)
			{
				delete(mesh);
				mesh = 0;
			}

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
