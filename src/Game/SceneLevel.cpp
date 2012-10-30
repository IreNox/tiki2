
#include "Game/SceneLevel.h"

#include "Game/GameState.h"

#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"
#include "Core/IMeshRenderer.h"
#include "Core/LibraryManager.h"

#include "Core/LightObject.h"
#include "Core/CameraObject.h"

#include "Game/CameraRTS.h"

using namespace TikiEngine::Objects;
using namespace TikiEngine::Scripts;

#include <sstream>
using namespace std;

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		SceneLevel::SceneLevel(Engine* engine)
			: Scene(engine), db(0), level(0), enemies(), objects()
		{
			sqlite3_open("Data/TikiData.sqlite", &db);

			gameState = new GameState(engine, this);
			gameState->AddRef();
		}

		SceneLevel::~SceneLevel()
		{
			this->DisposeLevel();
			SafeRelease(&gameState);

			if (db != 0)
			{
				sqlite3_close(db);
				db = 0;
			}
		}
		#pragma endregion

		#pragma region Member - Init
		void SceneLevel::Initialize(const InitializationArgs& args)
		{
			//Light
			LightObject* lo = new LightObject(engine);
			lo->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
			lo->GetLight()->SetColor(Color::White);
			lo->GetLight()->SetRange(1000);
			this->AddElement(lo);

			// Camera
			CameraObject* go = new CameraObject(engine);
			go->PRS.SPosition().Y = 35.0f;
			(new CameraRTS(engine, go));

			mainCamera = go->GetCameraComponent();
			this->AddElement(go);
			
			Scene::Initialize(args);
		}
		#pragma endregion

		#pragma region Member - Get
		Level* SceneLevel::GetLevel()
		{
			return level;
		}

		List<LevelObject*>* SceneLevel::GetObjects()
		{
			return &objects;
		}

		Camera* SceneLevel::GetCamera()
		{
			return mainCamera;
		}
		#pragma endregion

		#pragma region Member - Level
		bool SceneLevel::LoadLevel(Int64 id)
		{
			if (level != 0)
			{
				this->DisposeLevel();
			}

			const char* tmp = 0;
			sqlite3_stmt* state = 0;

			ostringstream sql;
			sql << "SELECT * FROM \"tiki_level\" WHERE \"ID\" = '" << id << "';";

			int r = sqlite3_prepare(db, sql.str().c_str(), sql.str().size(), &state, &tmp);

			if (r != SQLITE_OK || sqlite3_step(state) != SQLITE_ROW)
			{
				return false;
			}

			level = new Level(gameState);
			level->LoadFromDatabase(state);
			level->AddRef();
			sqlite3_finalize(state);

			// Load Enemies
			sql = ostringstream();
			sql << "SELECT * FROM \"tiki_level_enemies\" WHERE \"LevelID\" = '" << id << "';";

			r = sqlite3_prepare(db, sql.str().c_str(), sql.str().size(), &state, &tmp);

			if (r == SQLITE_OK)
			{
				while (sqlite3_step(state) == SQLITE_ROW)
				{
					LevelEnemy* enemy = new LevelEnemy(gameState);
					enemy->LoadFromDatabase(state);
					enemy->AddRef();

					enemies.Add(enemy);
				}
				sqlite3_finalize(state);
			}

			// Load Objects
			sql = ostringstream();
			sql << "SELECT * FROM \"tiki_level_objects\" WHERE \"LevelID\" = '" << id << "';";

			r = sqlite3_prepare(db, sql.str().c_str(), sql.str().size(), &state, &tmp);

			if (r == SQLITE_OK)
			{
				while (sqlite3_step(state) == SQLITE_ROW)
				{
					LevelObject* object = new LevelObject(gameState);
					object->LoadFromDatabase(state);
					object->AddRef();

					objects.Add(object);
				}
				sqlite3_finalize(state);
			}

			return gameState->LoadLevel(level);
		}

		void SceneLevel::DisposeLevel()
		{
			if (level == 0) return;

			UInt32 i = 0;
			while (i < enemies.Count())
			{
				SafeRelease(&enemies[i]);
				i++;
			}
			enemies.Clear();

			i = 0;
			while (i < objects.Count())
			{
				SafeRelease(&objects[i]);
				i++;
			}
			objects.Clear();

			SafeRelease(&level);
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void SceneLevel::Draw(const DrawArgs& args)
		{
			if (level) level->Draw(args);
			
			UInt32 i = 0;
			while (i < enemies.Count())
			{
				enemies[i]->Draw(args);
				i++;
			}

			i = 0;
			while (i < objects.Count())
			{
				objects[i]->Draw(args);
				i++;
			}

			gameState->Draw(args);
			Scene::Draw(args);
		}

		void SceneLevel::Update(const UpdateArgs& args)
		{
			#if _DEBUG
			if (args.Input.GetKeyPressed(KEY_F1))
			{
				//this->lighting.Properties.IsDirty = true;
				//this->lighting.Properties.DefaultShading = this->lighting.Properties.DefaultShading;
			}
			#endif

			if (level) level->Update(args);

			UInt32 i = 0;
			while (i < enemies.Count())
			{
				enemies[i]->Update(args);
				i++;
			}

			i = 0;
			while (i < objects.Count())
			{
				objects[i]->Update(args);
				i++;
			}

			gameState->Update(args);
			Scene::Update(args);
		}
		#pragma endregion
	}
}