#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	namespace Game
	{
		class GameState;

		class Skill : public EngineObject
		{
		public:

			Skill(GameState* state);
			~Skill();

			void Aktivate();
			virtual void CancelActivation() = 0;

			virtual void Draw(const DrawArgs& args) = 0;
			virtual void Update(const UpdateArgs& args) = 0;

		protected:

			bool passiv;
			double cooldown;

			virtual void internActivation() = 0;

		};
	}
}