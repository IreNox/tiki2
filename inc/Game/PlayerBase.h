#pragma once

#include "Game/GamePart.h"

#include "Core/GameObject.h"
#include "Game/LevelPoint.h"

namespace TikiEngine
{
	namespace Game
	{
		class PlayerBase : public GamePart
		{
		public:

			LevelPoint* SpawnPoint;

			GameObject* Hero;
			GameObject* MainBuilding;

			PlayerBase(GameState* state);
			~PlayerBase();
			
			void Init();

		};
	}
}