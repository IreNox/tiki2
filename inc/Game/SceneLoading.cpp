
#include "Game/SceneLoading.h"

#include "Core/ISpriteBatch.h"

namespace TikiEngine
{
	namespace Game
	{
		SceneLoading::SceneLoading(Engine* engine)
			: Scene(engine), circle(0)
		{
		}

		SceneLoading::~SceneLoading()
		{
			SafeRelease(&circle);
		}

		void SceneLoading::Initialize(const InitializationArgs& args)
		{
			circle = args.Content->LoadTexture(L"hud/loading");

			Scene::Initialize(args);
		}

		void SceneLoading::Draw(const DrawArgs& args)
		{
			args.SpriteBatch->Draw(
				circle,
				args.Graphics->GetViewPort()->GetSize() / 2,
				0.0,
				circle->GetCenter(),
				Vector2::One,
				1.0f,
				Color::White,
				-(float)args.Time.TotalTime / 4
			);

			Scene::Draw(args);
		}
	}
}