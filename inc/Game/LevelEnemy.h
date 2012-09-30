#pragma once

#include "Game/LevelChild.h"

namespace TikiEngine
{
	namespace Game
	{
		class LevelEnemy : public LevelChild
		{
		public:

			LevelEnemy(Engine* engine);
			~LevelEnemy();

		protected:

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}