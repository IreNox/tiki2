#pragma once

#include "Core/EngineObject.h"
#include "Core/TikiTimer.h"

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
			void Update(const UpdateArgs& args);

		protected:

			bool isPassiv;
			TikiTimer cooldownTimer;

			GameState* gameState;

			virtual void internActivation() = 0;
			virtual void internUpdate(const UpdateArgs& args) = 0;

		private:

			bool isReady;

		};
	}
}