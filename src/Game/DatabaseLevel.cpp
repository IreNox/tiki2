
#include "Game/BasicDatabase.h"
#include "Game/BasicTransform.h"
#include "Game/Level.h"
#include "Game/LevelPoint.h"
#include "Game/LevelObject.h"

#include "Game/Trigger.h"
#include "Game/SceneLevel.h"
#include "Game/TikiBotFactory.h"

#include "Core/LibraryManager.h"
#include "Core/IContentManager.h"
#include "Core/ITerrainRenderer.h"

#include "Game/EnemyBase.h"
#include "Game/PlayerBase.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region BasicDatabase
		BasicDatabase::BasicDatabase()
			: id(0)
		{
		}

		BasicDatabase::~BasicDatabase()
		{
		}

		void BasicDatabase::LoadFromDatabase(sqlite3_stmt* state)
		{
			Int32 i = 0;
			Int32 count = sqlite3_column_count(state);

			while (i < count)
			{
				string name = sqlite3_column_name(state, i);

				databaseToField(name, state, i);

				i++;
			}
		}

		Int64 BasicDatabase::GetId()
		{
			return id;
		}

		void BasicDatabase::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId) 
		{
			if (fieldName == "ID")
			{
				id = sqlite3_column_int64(state, fieldId);
			}
		}
		#pragma endregion

		#pragma region BasicTransform
		BasicTransform::BasicTransform(GameState* state)
			: BasicDatabase(), GameObject(state->GetEngine()), gameState(state)
		{
		}

		BasicTransform::~BasicTransform()
		{
		}

		void BasicTransform::LoadFromDatabase(sqlite3_stmt* state)
		{
			BasicDatabase::LoadFromDatabase(state);

			SceneLevel* scene = (SceneLevel*)engine->GetScene();
			if (scene && scene->GLevel()->GetTerrain())
			{
				this->PRS.SPosition().Y = scene->GLevel()->GetTerrain()->SampleHeight(this->PRS.GPosition());
			}			
		}

		void BasicTransform::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "PositionX")
			{
				this->PRS.SPosition().X = (float)sqlite3_column_double(state, fieldId);
			}
			else if (fieldName == "PositionY")
			{
				this->PRS.SPosition().Z = (float)sqlite3_column_double(state, fieldId);
			}
			else if (fieldName == "Scale" && this->PRS.GScale() == Vector3::One)
			{
				this->PRS.SScale() = Vector3(
					(float)sqlite3_column_double(state, fieldId)
					);
			}
			else if (fieldName == "Rotation")
			{
				this->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(
					(float)sqlite3_column_double(state, fieldId), 0, 0
				);
			}

			BasicDatabase::databaseToField(fieldName, state, fieldId);
		}
		#pragma endregion

		#pragma region Level
		Level::Level(GameState* state)
			: BasicDatabase(), GameObject(state->GetEngine()), terrain(0), collider(0), frameCount(0), gameState(state)
		{
			terrain = engine->librarys->CreateComponent<ITerrainRenderer>(this);
			terrain->AddRef();
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
				mat->TexDiffuse = engine->content->LoadTexture(L"terrain/color_" + StringAtoW(name));
				mat->TexLightMap = engine->content->LoadTexture(L"terrain/terrain_rock");
				mat->TexNormalMap = engine->content->LoadTexture(L"terrain/Terrain_Sand");
				mat->TexSpecularMap = engine->content->LoadTexture(L"terrain/Terrain_Grass");
				mat->GetShader()->SetVector2("TerrainSize", Vector2((float)heightmapSize, (float)heightmapSize));
				terrain->SetMaterial(mat);
				terrain->LoadTerrain(
					heightmapFilename, heightmapScale, heightmapSize, heightmapElevation
#if _DEBUG
					, true
#endif					
				);

				IPhysicsMaterial* material = engine->librarys->CreateResource<IPhysicsMaterial>();
				material->SetRestitution(0.2f);
				material->SetDynamicFriction(0.7f);
				material->SetStaticFriction(0.5f);

				collider = engine->librarys->CreateComponent<ITriangleMeshCollider>(this);
				collider->SetMaterial(material);
				collider->SetCenter(Vector3::Zero);
				collider->SetDynamic(false);
				collider->SetGroup(CG_Collidable_Non_Pushable);
				collider->AddRef();

				Mesh* mesh = engine->content->LoadMesh(L"collider/collider_" + StringAtoW(name));

				UInt32 indexCount;
				UInt32* indexData;
				mesh->GetIndexData(&indexData, &indexCount);

				UInt32 vertexLength;
				DefaultVertex* vertexData;
				mesh->GetVertexData((void**)&vertexData, &vertexLength);

				UInt32 i = 0;
				UInt32 vertexCount = vertexLength / sizeof(DefaultVertex);
				Vector3* vertices = TIKI_NEW Vector3[vertexCount];
				while (i < vertexCount) { vertices[i] = vertexData[i].Position; i++; }

				collider->SetMeshData(indexData, indexCount, vertices, vertexCount);

				delete[](vertices);
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
			else if (fieldName == "HeightmapElevation")
			{			
				heightmapElevation = (float)sqlite3_column_double(state, fieldId);
			}
		}

		void Level::Update(const UpdateArgs& args)
		{
			GameObject::Update(args);

			//if (frameCount % 10 == 0 && frameCount < 100)
			//{
			//	float hSize = (float)heightmapSize / 2;

			//	List<Vector3> poi;
			//	Vector3 pos = Vector3::Zero;

			//	for (float x = -hSize; x <= hSize; x += 64)
			//	{
			//		pos.X = x;

			//		for (float y = -hSize; y <= hSize; y += 64)
			//		{
			//			pos.Z = y;
			//			pos.Y = terrain->SampleHeight(pos) + 5;

			//			poi.Add(pos);
			//		}
			//	}

			//}
			//frameCount++;
		}
		#pragma endregion
		
		#pragma region LevelPoint
		LevelPoint::LevelPoint(GameState* state)
			: BasicDatabase(), type(0), name(), position(), gameState(state)
		{
		}

		LevelPoint::~LevelPoint()
		{
		}

		void LevelPoint::LoadFromDatabase(sqlite3_stmt* state)
		{
			BasicDatabase::LoadFromDatabase(state);

			switch (type)
			{
			case 2:
				gameState->GetPart<EnemyBase>(assignment)->WayPoints.Add(position);
				break;
			case 3:
				gameState->GetPart<EnemyBase>(assignment)->SpawnPoint = this;
				break;
			}
		}

		void LevelPoint::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "Name")
			{
				name = (char*)sqlite3_column_text(state, fieldId);
			}
			else if (fieldName == "PositionX")
			{
				position.X = (float)sqlite3_column_double(state, fieldId);
			}
			else if (fieldName == "PositionY")
			{
				position.Y = (float)sqlite3_column_double(state, fieldId);
			}
			else if (fieldName == "Type")
			{
				type = sqlite3_column_int(state, fieldId);
			}
			else if (fieldName == "Assignment")
			{
				assignment = sqlite3_column_int(state, fieldId);
			}

			BasicDatabase::databaseToField(fieldName, state, fieldId);
		}
		#pragma endregion

		#pragma region LevelObject
		LevelObject::LevelObject(GameState* state)
			: BasicTransform(state), type(0)
		{
		}

		LevelObject::~LevelObject()
		{
		}

		Int64 LevelObject::GetLevelID()
		{
			return levelId;
		}

		void LevelObject::LoadFromDatabase(sqlite3_stmt* state)
		{
			BasicTransform::LoadFromDatabase(state);

			switch (type)
			{
			case 0:
				this->SModel(engine->content->LoadModel(L"replaceme_cube"));
				gameState->GetScene()->AddElement(this);
				break;
			case 1: // player
				gameState->GetBotFactory()->CreatePlayerMob(this, Vector3::Zero);
				break;
			case 2: // enemy
				gameState->GetBotFactory()->CreateEnemyMob(this, List<Vector2>());
				break;
			case 3: // Hero Platform
				gameState->GetBotFactory()->CreatePlayerHeroPlatform(this);
				break;
			case 4:
				this->SModel(engine->content->LoadModel(L"building_03_05"));
				gameState->GetScene()->AddElement(this);
				break;
			case 5:
				this->SModel(engine->content->LoadModel(L"env_pipe_01"));
				gameState->GetScene()->AddElement(this);
				break;
			case 6: // Rocks
			case 7:
			case 8:
				{
					this->SModel(
						engine->content->LoadModel(
							L"rock_0" + StringConvert::ToWString(type - 5)
						)
					);
					gameState->GetScene()->AddElement(this);
				}
				break;
			case 14: // Trees
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
				{
					this->PRS.SScale() *= 0.01f;
					this->SModel(
						engine->content->LoadModel(
							L"tree0" + StringConvert::ToWString(type - 13)
						)
					);
					gameState->GetScene()->AddElement(this);
				}
				break;
			case 22: // Ruins
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
				{
					this->PRS.SScale() *= 0.01f;
					this->SModel(
						engine->content->LoadModel(
							L"ruin_0" + StringConvert::ToWString(type - 21)
						)
					);
					gameState->GetScene()->AddElement(this);
				}
				break;
			case 9: // Tower Build slot
				gameState->GetBotFactory()->CreateBuildSlot(this);
				break;
			case 10:
				gameState->GetBotFactory()->CreateEnemyBuilding(this);
				gameState->GetPart<EnemyBase>(assignment)->GateControl = this;
				break;
			case 11:
				gameState->GetBotFactory()->CreatePlayerMainBuilding(this);
				break;
			case 12:
				gameState->GetBotFactory()->CreateEnemyTower(this);
				break;
			case 13:
				gameState->GetBotFactory()->CreatePlayerTower(this);
				break;
			case 28:
				gameState->GetBotFactory()->CreatePlayerSpawnBuilding(this);
				break;
			case 29:
				gameState->GetBotFactory()->CreatePlayerResearchBuilding(this);
				break;
			case 30:
				{
					this->PRS.SScale() *= 0.01f;
					this->SModel(engine->content->LoadModel(L"bolder"));
					gameState->GetScene()->AddElement(this);
				}
				break;
			case 31:
				{
					this->PRS.SScale() *= 0.01f;
					this->SModel(engine->content->LoadModel(L"crates_01"));
					gameState->GetScene()->AddElement(this);
				}
				break;
			case 32:
				{
					this->PRS.SScale() *= 0.01f;
					this->SModel(engine->content->LoadModel(L"crates_02"));
					gameState->GetScene()->AddElement(this);
				}
				break;
			default:
				throw "Wrong Object Type";
			}
		}

		void LevelObject::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "Type")
			{
				type = sqlite3_column_int(state, fieldId);
			}
			else if (fieldName == "LevelID")
			{
				levelId = sqlite3_column_int64(state, fieldId);
			}
			else if (fieldName == "Assignment")
			{
				assignment = sqlite3_column_int(state, fieldId);
			}

			BasicTransform::databaseToField(fieldName, state, fieldId);
		}
		#pragma endregion
	}
}