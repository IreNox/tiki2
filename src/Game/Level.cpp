
#include "Game/Level.h"

#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"

#include "Core/ITerrainRenderer.h"

namespace TikiEngine
{
	namespace Game
	{
		Level::Level(GameState* state)
			: BasicDatabase(state), terrain(0), collider(0), frameCount(0)
		{
		}

		Level::~Level()
		{
			SafeRelease(&terrain);
			SafeRelease(&collider);
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
				terrain->AddRef();

				IPhysicsMaterial* material = engine->librarys->CreateResource<IPhysicsMaterial>();
				material->SetRestitution(0.2f);
				material->SetDynamicFriction(0.7f);
				material->SetStaticFriction(0.5f);

				collider = engine->librarys->CreateComponent<ITriangleMeshCollider>(this);
				collider->SetMaterial(material->GetIndex());
				collider->SetCenter(Vector3::Zero);
				collider->SetDynamic(false);
				collider->SetGroup(CG_Collidable_Non_Pushable);
				collider->AddRef();
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
			BasicDatabase::Update(args);

			if (frameCount % 10 == 0 && frameCount < 100)
			{
				float hSize = (float)heightmapSize / 2;

				List<Vector3> poi;
				Vector3 pos = Vector3::Zero;

				for (float x = -hSize; x <= hSize; x += 16)
				{
					pos.X = x;

					for (float y = -hSize; y <= hSize; y += 16)
					{
						pos.Z = y;
						pos.Y = terrain->SampleHeight(pos) + 5;

						poi.Add(pos);
					}
				}

				terrain->UpdateCollider(collider, &poi);
			}
			frameCount++;
		}
	}
}