
#include "Game/SceneLevel.h"

namespace TikiEngine
{
	namespace Game
	{
		SceneLevel::SceneLevel(Engine* engine)
			: Scene(engine), db(0)
		{
		}

		SceneLevel::~SceneLevel()
		{
			if (db)
			{
				sqlite3_close(db);
				db = 0;
			}
		}

		void SceneLevel::Initialize(const InitializationArgs& args)
		{
			sqlite3_open("Data/TikiData.sqlite", &db);

			string sql = "SELECT * FROM \"tiki_level\"";

			sqlite3_stmt* state;
			const char* test;
			const unsigned char* test2;

			int r = sqlite3_prepare(db, sql.c_str(), sql.size(), &state, &test);

			List<int> fieldTypes;
			List<string> fieldNames;

			int count = sqlite3_column_count(state);
			for (int i = 0; i < count; i++)
			{
				int type = sqlite3_column_type(state, i);
				const char* name = sqlite3_column_name(state, i);

				fieldTypes.Add(type);
				fieldNames.Add(name);
			}


			test2 = sqlite3_column_text(state, 1);

			r = sqlite3_step(state);
			r = sqlite3_step(state);
			r = sqlite3_step(state);

			test2 = sqlite3_column_text(state, 1);

			r = sqlite3_finalize(state);

			sqlite3_int64 bla;

			// my code

			Scene::Initialize(args);
		}
	}
}