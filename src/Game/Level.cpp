
#include "Game/Level.h"

#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Core/ITerrainRenderer.h"

namespace TikiEngine
{
	namespace Game
	{
		Level::Level(Engine* engine)
			: BasicDatabase(engine), terrain(0)
		{
		}

		Level::~Level()
		{
			SafeRelease(&terrain);
		}

		ITerrainRenderer* Level::GetTerrain()
		{
			return terrain;
		}

		void Level::LoadFromDatabase(sqlite3_stmt* state)
		{
			BasicDatabase::LoadFromDatabase(state);

			if (heightmapFilename != "" && heightmapScale != 0 && heightmapSize != 0)
			{
				Material* mat = engine->content->LoadMaterial(L"os_cloddy");
				terrain = engine->librarys->CreateComponent<ITerrainRenderer>(this);
				terrain->LoadTerrain(heightmapFilename, heightmapScale, heightmapSize);
				terrain->SetMaterial(mat);
				mat->Release();
			}
		}

		void Level::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "Name")
			{			
				name = (const char *)sqlite3_column_text(state, fieldId);
			}
			else if (fieldName == "HeightmapFilename")
			{			
				heightmapFilename = (const char *)sqlite3_column_text(state, fieldId);
			}
			else if (fieldName == "HeightmapScale")
			{			
				heightmapScale = sqlite3_column_int(state, fieldId);
			}
			else if (fieldName == "HeightmapSize")
			{			
				heightmapSize = sqlite3_column_int(state, fieldId);
			}
		}
	}
}