
#include "Game/SceneMark.h"

namespace TikiEngine
{
	namespace Game
	{
		SceneMark::SceneMark(Engine* engine)
			: Scene(engine)
		{
		}

		SceneMark::~SceneMark()
		{
		}

		void SceneMark::Initialize(const InitializationArgs& args)
		{
			// Code hier

			Scene::Initialize(args);
		}

		void SceneMark::Draw(const DrawArgs& args)
		{
			Scene::Draw(args);
		}

		void SceneMark::Update(const UpdateArgs& args)
		{
			Scene::Update(args);
		}
	}
}