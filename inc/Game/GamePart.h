#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	namespace Game
	{
		class GameState;

		class GamePart : public EngineObject
		{
		public:

			GamePart(GameState* state);
			~GamePart();

			virtual void Init();
			virtual void Draw(const DrawArgs& args);
			virtual void Update(const UpdateArgs& args);

			inline int GetID() { return id; }
			inline void SetID(int ids) { id = ids; }

		protected:

			int id;

			GameState* gameState;

		};
	}
}