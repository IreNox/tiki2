#pragma once

#include "Core/EngineObject.h"
#include "Core/ITexture.h"
#include "Core/ISound.h"

#include "Game/GameState.h"

#include <functional>
using std::function;

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Resources;

		struct Announcement
		{
			wstring Message;

			ISound* Sound;
			ITexture* Icon;
		};

		class Announcer : public EngineObject
		{
		public:

			Announcer(GameState* state);
			~Announcer();

			Announcement* Announce(const wstring& msg, const wstring& icon = L"", const wstring& sound = L"", function<void(void)> funcActivate = 0);

			void ActivateAnnouncement(Announcement* announcement);						 

		private:

			GameState* gameState;

			List<Announcement*> announcements;

		};
	}
}