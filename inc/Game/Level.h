#pragma once

#include "Game/BasicDatabase.h"

#include "Core/ITerrainRenderer.h"
#include "Core/ITriangleMeshCollider.h"

namespace TikiEngine
{
	namespace Game
	{
		class Level : public BasicDatabase
		{
		public:

			Level(GameState* state);
			~Level();

			void LoadFromDatabase(sqlite3_stmt* state);

			string GetName();
			ITerrainRenderer* GetTerrain();

			void Update(const UpdateArgs& args);

		private:

			string name;

			string heightmapFilename;
			int heightmapScale;
			int heightmapSize;

			UInt32 colliderUpdate;
			ITerrainRenderer* terrain;
			ITriangleMeshCollider* collider;

		protected:

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}