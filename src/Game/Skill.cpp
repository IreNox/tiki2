
#include "Game/Skill.h"

#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{
		Skill::Skill(GameState* state)
			: EngineObject(state->GetEngine()), gameState(state), cooldownTimer(1.0)
		{
		}

		Skill::~Skill()
		{
		}

		void Skill::Aktivate()
		{
			if (isReady && !isPassiv)
			{
				internActivation();
			}
			else if (!isReady)
			{
				// play sound
			}
		}

		void Skill::Update(const UpdateArgs& args)
		{
			if (!isReady)
			{
				isReady = cooldownTimer.IsReady(args.Time);
			}
		}
	}
}