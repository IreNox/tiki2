#pragma once

#include "Core/TypeGlobals.h"

#include "Core/GameObject.h"
#include "Core/sqlite3.h"

#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{
		class BasicDatabase : public GameObject
		{
		public:

			BasicDatabase(GameState* state);
			~BasicDatabase();

			virtual void LoadFromDatabase(sqlite3_stmt* state);

			Int64 GetId();

		protected:

			Int64 id;

			GameState* gameState;

			virtual void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}