
#include "Game/SceneLevel.h"

#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"
#include "Core/IMeshRenderer.h"
#include "Core/LibraryManager.h"

#include "Core/LightObject.h"
#include "Core/CameraObject.h"

#include "Game/CameraFly.h"

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
		}

		SceneLevel::~SceneLevel()
		{
			this->DisposeLevel();

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
			//GameObject* go = new GameObject(engine);

			/*Mesh* mesh = engine->content->LoadMesh(L"Data/Resources/Models/box_ursprung.fbx");
			ITexture* tex = engine->content->LoadTexture(L"Data/Resources/Textures/box_diffuse.jpg");

			Material* mat = engine->content->LoadMaterial(L"Data\\Effects\\os_default.fx");
			mat->GetShader()->SetTexture("tex", tex);
			tex->Release();

			IMeshRenderer* render = engine->librarys->CreateComponent<IMeshRenderer>(go);
			render->SetMesh(mesh);
			render->SetMaterial(mat);
			mat->Release();
			mesh->Release();
			render->Release();

			this->AddElement(go);
			go->Release();*/

			//Light
			LightObject* lo = new LightObject(engine);
			lo->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(1, 0, 1);
			lo->GetLight()->SetColor(Color::White);
			lo->GetLight()->SetRange(1000);

			this->AddElement(lo);
			lo->Release();

			// Camera
			GameObject* go = new CameraObject(engine);
			go->PRS.Position.Z = 5.0f;

			CameraFly* fly = new CameraFly(engine, go);
			fly->Release();

			this->AddElement(go);
			go->Release();
			
			Scene::Initialize(args);
		}
		#pragma endregion

		#pragma region Member
		Level* SceneLevel::GetLevel()
		{
			return level;
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

			level = new Level(engine);
			level->LoadFromDatabase(state);
			sqlite3_finalize(state);

			// Load Enemies
			sql = ostringstream();
			sql << "SELECT * FROM \"tiki_level_enemies\" WHERE \"LevelID\" = '" << id << "';";

			r = sqlite3_prepare(db, sql.str().c_str(), sql.str().size(), &state, &tmp);

			if (r != SQLITE_OK)
			{
				return false;
			}

			while (sqlite3_step(state) == SQLITE_ROW)
			{
				LevelEnemy* enemy = new LevelEnemy(engine);
				enemy->LoadFromDatabase(state);

				enemies.Add(enemy);
			}
			sqlite3_finalize(state);

			// Load Objects
			sql = ostringstream();
			sql << "SELECT * FROM \"tiki_level_objects\" WHERE \"LevelID\" = '" << id << "';";

			r = sqlite3_prepare(db, sql.str().c_str(), sql.str().size(), &state, &tmp);

			if (r != SQLITE_OK)
			{
				return false;
			}

			while (sqlite3_step(state) == SQLITE_ROW)
			{
				LevelObject* object = new LevelObject(engine);
				object->LoadFromDatabase(state);

				objects.Add(object);
			}
			sqlite3_finalize(state);

			return true;
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

			engine->sprites->Draw(
				engine->graphics->GetDepthTarget(),
				Rectangle(10, 10, 200, 180)
			);

			engine->sprites->Draw(
				engine->graphics->GetNormalTarget(),
				Rectangle(10, 200, 200, 180)
			);

			Scene::Draw(args);
		}

		void SceneLevel::Update(const UpdateArgs& args)
		{
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

			Scene::Update(args);
		}
		#pragma endregion
	}
}