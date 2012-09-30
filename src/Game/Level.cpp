
#include "Game/Level.h"

namespace TikiEngine
{
	namespace Game
	{
		Level::Level(Engine* engine)
			: BasicDatabase(engine)
		{
		}

		Level::~Level()
		{
		}

		void Level::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "Name")
			{			
				name = (const char *)sqlite3_column_text(state, fieldId);
			}
			else if (fieldName == "HeightmapFilename")
			{			
				heightMap = (const char *)sqlite3_column_text(state, fieldId);
			}
		}
	}
}