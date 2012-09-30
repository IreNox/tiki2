#pragma once

#include "Core/TypeGlobals.h"

#include "Core/GameObject.h"
#include "Game/sqlite3.h"

namespace TikiEngine
{
	namespace Game
	{
		class BasicDatabase : public GameObject
		{
		public:

			BasicDatabase(Engine* engine);
			~BasicDatabase();

			virtual void LoadFromDatabase(sqlite3_stmt* state);

			Int64 GetId();

		protected:

			Int64 id;

			virtual void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}