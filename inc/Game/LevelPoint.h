#pragma once

#include "Core/TikiObject.h"
#include "Game/BasicDatabase.h"
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{
		class LevelPoint : public TikiObject, public BasicDatabase
		{
		public:

			LevelPoint(GameState* state);
			~LevelPoint();

			inline const Vector2& GPosition() { return position; }

			inline const Int32& GType() { return type; }
			inline const Int32& GAssignment() { return assignment; }

			inline const string& GName() { return name; }

			void LoadFromDatabase(sqlite3_stmt* state);

		protected:

			GameState* gameState;

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		private:

			Vector2 position;

			Int32 type;
			Int32 assignment;

			string name;

		};
	}
}