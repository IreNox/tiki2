#pragma once

#include "Core/Event.h"

namespace TikiEngine
{
	class GameObject;

	namespace AI
	{
		class TikiBot;

		struct HeroLevelUpEventArgs 
		{
			int HeroLevel;

			double HeroXP;
			double NextLevelXP;

			HeroLevelUpEventArgs(int level, double xp, double nextXp)
				: HeroLevel(level), HeroXP(xp), NextLevelXP(nextXp)
			{
			}
		};

		typedef Event<TikiBot, HeroLevelUpEventArgs> HeroLevelUpEvent;
		typedef EventHandler<TikiBot, HeroLevelUpEventArgs> HeroLevelUpEventHandler;
	}
}
