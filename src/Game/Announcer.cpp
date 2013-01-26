
#include "Game/Announcer.h"
#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Game
	{
		Announcer::Announcer(GameState* state)
			: EngineObject(state->GetEngine()), gameState(state)
		{
		}

		Announcer::~Announcer()
		{
			FOREACH(announcements, SafeDelete(&announcements[i]))
		}

		Announcement* Announcer::Announce(const wstring& msg, const wstring& icon /* = 0 */, const wstring& sound /* = 0 */, function<void(void)> funcActivate /* = 0 */)
		{
			Announcement* ann = TIKI_NEW Announcement();
			ann->Message = msg;

			if (!icon.Empty())
				ann->Icon = engine->content->LoadTexture(icon);

			if (!sound.Empty())
				ann->Sound = engine->content->LoadSound(sound);
			
			announcements.Add(ann);

			return ann;
		}
	}
}