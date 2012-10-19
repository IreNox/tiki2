
#include "Game/LevelChild.h"

#include "Core/LibraryManager.h"

namespace TikiEngine
{
	namespace Game
	{
		LevelChild::LevelChild(Engine* engine)
			: BasicTransform(engine)
		{
		}

		LevelChild::~LevelChild()
		{
		}

		void LevelChild::LoadFromDatabase(sqlite3_stmt* state)
		{
			BasicTransform::LoadFromDatabase(state);
		}

		Int64 LevelChild::GetLevelID()
		{
			return levelId;
		}

		void LevelChild::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "LevelID")
			{
				levelId = sqlite3_column_int64(state, fieldId);
			}

			BasicTransform::databaseToField(fieldName, state, fieldId);
		}
	}
}