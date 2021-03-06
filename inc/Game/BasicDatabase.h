#pragma once

#include "Core/TypeGlobals.h"

#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{
		class BasicDatabase
		{
		public:

			BasicDatabase();
			virtual ~BasicDatabase();

			virtual void LoadFromDatabase(sqlite3_stmt* state);

			Int64 GetId();

		protected:

			Int64 id;

			virtual void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}