
#include "Game/BasicDatabase.h"

namespace TikiEngine
{
	namespace Game
	{
		BasicDatabase::BasicDatabase(GameState* state)
			: GameObject(state->GetEngine()), gameState(state)
		{
		}

		BasicDatabase::~BasicDatabase()
		{
		}

		void BasicDatabase::LoadFromDatabase(sqlite3_stmt* state)
		{
			Int32 i = 0;
			Int32 count = sqlite3_column_count(state);

			while (i < count)
			{
				string name = sqlite3_column_name(state, i);

				databaseToField(name, state, i);

				i++;
			}
		}

		Int64 BasicDatabase::GetId()
		{
			return id;
		}

		void BasicDatabase::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId) 
		{
			if (fieldName == "ID")
			{
				id = sqlite3_column_int64(state, fieldId);
			}
		}
	}
}