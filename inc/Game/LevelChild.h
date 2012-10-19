#pragma once

#include "Game/BasicTransform.h"

#include "Core/IMeshRenderer.h"

namespace TikiEngine
{
	namespace Game
	{
		class LevelChild : public BasicTransform
		{
		public:

			LevelChild(Engine* engine);
			~LevelChild();

			void LoadFromDatabase(sqlite3_stmt* state);

			Int64 GetLevelID();

		protected:

			Int64 levelId;

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}