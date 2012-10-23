
#include "Game/Level.h"

#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Core/ITerrainRenderer.h"

namespace TikiEngine
{
	namespace Game
	{
		Level::Level(GameState* state)
			: BasicDatabase(state), terrain(0), collider(0), colliderUpdate(0)
		{
		}

		Level::~Level()
		{
			SafeRelease(&terrain);
		}

		string Level::GetName()
		{
			return name;
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

				IPhysicsMaterial* material = engine->librarys->CreateResource<IPhysicsMaterial>();
				material->SetRestitution(0.2f);
				material->SetDynamicFriction(0.7f);
				material->SetStaticFriction(0.5f);

				collider = engine->librarys->CreateComponent<ITriangleMeshCollider>(this);
				collider->SetMaterial(material->GetIndex());
				collider->SetCenter(Vector3::Zero);
				collider->SetDynamic(false);
				collider->SetGroup(CG_Collidable_Non_Pushable);
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

		void Level::Update(const UpdateArgs& args)
		{
			List<GameObject*> poi;
			poi.Add(this);

			if (colliderUpdate++ > 5)
			{
				terrain->UpdateCollider(collider, &poi);
				colliderUpdate = 0;
			}

			BasicDatabase::Update(args);
		}
	}
}