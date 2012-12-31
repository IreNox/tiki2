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
			double HeroXP;
			double NextLevelXP;

			HeroLevelUpEventArgs(double xp, double nextXp) : HeroXP(xp), NextLevelXP(nextXp) { }
		};

		typedef Event<TikiBot, HeroLevelUpEventArgs> HeroLevelUpEvent;
		typedef EventHandler<TikiBot, HeroLevelUpEventArgs> HeroLevelUpEventHandler;
	}
}
