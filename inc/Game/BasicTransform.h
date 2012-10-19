#pragma once

#include "Game/BasicDatabase.h"

namespace TikiEngine
{
	namespace Game
	{
		class BasicTransform : public BasicDatabase
		{
		public:

			BasicTransform(GameState* state);
			~BasicTransform();

			void LoadFromDatabase(sqlite3_stmt* state);

		protected:

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}