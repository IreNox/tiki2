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
			bool ShowAtScreenCenter;

			ISound* Sound;
			ITexture* Icon;

			double ShowDuration;
		};

		class Announcer : public EngineObject
		{
		public:

			Announcer(GameState* state);
			~Announcer();

			Announcement* Announce(const wstring& msg, bool showAtScreenCenter = false, const wstring& icon = L"", const wstring& sound = L"", function<void(void)> funcClick = 0);

			void ActivateAnnouncement(Announcement* announcement);						 

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			GameState* gameState;

			List<Announcement*> announcements;

		};
	}
}