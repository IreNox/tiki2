#pragma once

#include "Game/LevelChild.h"

namespace TikiEngine
{
	namespace Game
	{
		class LevelObject : public LevelChild
		{
		public:

			LevelObject(GameState* state);
			~LevelObject();

			void LoadFromDatabase(sqlite3_stmt* state);

		private:

			Int32 type;

		protected:

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}