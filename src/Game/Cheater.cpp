
#include "Game/Cheater.h"

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
			if (cheat == L"show me the money")
			{
				gameState->IncrementResource(10000.0);
			}
			else if (cheat == L"if bleeds we can kill it")
			{
				//this->GetPart<PlayerBase>(0)->Hero->GetComponent<TikiBot>()->GetWeaponSys()->GetWeapon
			}
		}
	}
}