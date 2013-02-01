
#include "Game/Announcer.h"

#include "Core/ISpriteBatch.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		Announcer::Announcer(GameState* state)
			: EngineObject(state->GetEngine()), gameState(state)
		{
		}

		Announcer::~Announcer()
		{
			FOREACH_CODE(announcements, SafeDelete(&announcements[i]))
		}
		#pragma endregion

		#pragma region Member - Announce
		Announcement* Announcer::Announce(const wstring& msg, bool showAtScreenCenter, const wstring& icon /* = 0 */, const wstring& sound /* = 0 */, function<void(void)> funcActivate /* = 0 */)
		{
			Announcement* ann = TIKI_NEW Announcement;
			ann->Message = msg;
			ann->ShowAtScreenCenter = showAtScreenCenter;
			ann->ShowDuration = 7.0;

			if (!icon.Empty())
				ann->Icon = engine->content->LoadTexture(icon);

			if (!sound.Empty())
				ann->Sound = engine->content->LoadSound(sound);
			
			announcements.Add(ann);

			return ann;
		}
		#pragma endregion

		#pragma region Member - Draw
		void Announcer::Draw(const DrawArgs& args)
		{
			FOREACH_PTR(Announcement, ann, announcements)
				args.SpriteBatch->DrawString(
					gameState->GetDefaultFont(),
					ann->Message,
					Vector2(10, 400 + (float)(i * 25)),
					Color::White
				);
			FOREACH_END
		}
		#pragma endregion

		#pragma region Member - Update
		void Announcer::Update(const UpdateArgs& args)
		{
			FOREACH_PTR(Announcement, ann, announcements)
				ann->ShowDuration -= args.Time.ElapsedTime;

				if (ann->ShowDuration < 0.0)
				{
					announcements.Remove(ann);
					SafeDelete(&ann);
				}
			FOREACH_END
		}
		#pragma endregion
	}
}