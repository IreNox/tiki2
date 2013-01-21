
#include "Game/Cheater.h"

#include "Game/Weapon.h"
#include "Game/TikiBot.h"
#include "Game/PlayerBase.h"
#include "Game/SkillSystem.h"
#include "Game/WeaponSystem.h"

namespace TikiEngine
{
	namespace Game
	{
		Cheater::Cheater(GameState* state)
			: EngineObject(state->GetEngine()), gameState(state)
		{
		}

		Cheater::~Cheater()
		{
		}

		void Cheater::DoCheat(const wstring& cheat)
		{
			if (cheat == L"give me the money")
			{
				gameState->IncrementResource(10000.0);
			}
			else if (cheat == L"if bleeds i can kill it")
			{
				gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetWeaponSys()->GetCurrentWeapon()->SetDamage(100000);
			}
			else if (cheat == L"my brain is faster")
			{
				gameState->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetSkillSys()->IncementXP(1000000);
			}
			else if (cheat == L"krumnovovov")
			{
				throw "dead";
			}
		}
	}
}