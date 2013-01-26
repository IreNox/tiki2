
#include "Core/DatabaseState.h"

namespace TikiEngine
{
	#pragma region Class
	DatabaseState::DatabaseState(Engine* engine)
		: EngineObject(engine), state(0), dataLength(0), data(0)
	{
	}

	DatabaseState::~DatabaseState()
	{
		if (state)
		{
			sqlite3_finalize(state);
			state = 0;
		}

		SafeDeleteArray(&data);
	}
	#pragma endregion

	#pragma region Member - Query
	bool DatabaseState::Query(const string& sql)
	{
		const char* tmp = 0;
		int r = sqlite3_prepare(
			engine->GetDB(),
			sql.CStr(),
			(int)sql.Length(),
			&state,
			&tmp
		);

		return (r == SQLITE_OK);
	}
	#pragma endregion

	#pragma region Member - ReadNextRow
	bool DatabaseState::ReadNextRow()
	{
		int r = sqlite3_step(state);

		if (r == SQLITE_ROW)
		{
			UInt32 typeLength[] = { 0, 32, 32, 0, 0, 0 };

			dataLength = 0;
			SafeDeleteArray(&data);
			fieldData.Clear();

			Int32 i = 0;
			Int32 count = sqlite3_column_count(state);

			while (i < count)
			{
				DatabaseTypes type = (DatabaseTypes)sqlite3_column_type(state, i);

				sqlite3_value* val = sqlite3_column_value(state, i);

				//val

				switch (type)
				{
				case DBT_Blob:
					//typeLength[DBT_Blob] = sqlite3_column_bl
					break;
				}

				i++;
			}

			return true;
		}

		return false;
	}
	#pragma endregion
}