#pragma once

#include "Game/BasicDatabase.h"

namespace TikiEngine
{
	namespace Game
	{
		class Level : public BasicDatabase
		{
		public:

			Level(Engine* engine);
			~Level();

		private:

			string name;
			string heightMap;

		protected:

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}