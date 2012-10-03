#pragma once

#include "Game/BasicDatabase.h"

#include "Core/ITerrainRenderer.h"

namespace TikiEngine
{
	namespace Game
	{
		class Level : public BasicDatabase
		{
		public:

			Level(Engine* engine);
			~Level();

			void LoadFromDatabase(sqlite3_stmt* state);

			ITerrainRenderer* GetTerrain();

		private:

			string name;

			string heightmapFilename;
			int heightmapScale;
			int heightmapSize;

			ITerrainRenderer* terrain;

		protected:

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}