#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	namespace Game
	{
		class GameState;

		class ISkill : public EngineObject
		{
		public:

			ISkill(GameState* state);
			~ISkill();

			virtual void Aktivate() = 0;
			virtual void CancelActivation() = 0;

			virtual void Draw(const DrawArgs& args) = 0;
			virtual void Update(const UpdateArgs& args) = 0;

		};
	}
}