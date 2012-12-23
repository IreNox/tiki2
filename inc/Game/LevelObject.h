#pragma once

#include "Game/BasicTransform.h"

namespace TikiEngine
{
	namespace Game
	{
		class LevelObject : public BasicTransform
		{
		public:

			LevelObject(GameState* state);
			~LevelObject();

			Int64 GetLevelID();

			void LoadFromDatabase(sqlite3_stmt* state);

		private:

			Int64 levelId;

			Int32 type;
			Int32 assignment;

		protected:

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}