#pragma once

#include "Game/BasicDatabase.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace Game
	{
		class BasicTransform : public GameObject, public BasicDatabase
		{
		public:

			BasicTransform(GameState* state);
			virtual ~BasicTransform();

			void LoadFromDatabase(sqlite3_stmt* state);

		protected:

			GameState* gameState;

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}