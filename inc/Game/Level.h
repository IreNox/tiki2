#pragma once

#include "Core/GameObject.h"

#include "Game/BasicDatabase.h"

#include "Core/ITerrainRenderer.h"
#include "Core/ITriangleMeshCollider.h"

namespace TikiEngine
{
	namespace Game
	{
		class Level : public GameObject, public BasicDatabase
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

			GameState* gameState;

			string heightmapFilename;
			int heightmapScale;
			int heightmapSize;
			float heightmapElevation;

			UInt32 frameCount;
			ITerrainRenderer* terrain;
			ITriangleMeshCollider* collider;

		protected:

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}