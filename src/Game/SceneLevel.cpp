
#include "Game/SceneLevel.h"

#include "Game/GameState.h"

#include "Core/IGraphics.h"
#include "Core/ISpriteBatch.h"
#include "Core/IMeshRenderer.h"
#include "Core/LibraryManager.h"

#include "Core/LightObject.h"
#include "Core/CameraObject.h"

#include "Game/CameraRTS.h"

#include "Game/PPBlur.h"
#include "Game/PPFogOfWar.h"
#include "Game/PPScreenSpaceAmbientOcclusion.h"

using namespace TikiEngine::Objects;
using namespace TikiEngine::Scripts;
using namespace TikiEngine::Graphics;

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		SceneLevel::SceneLevel(Engine* engine)
			: Scene(engine)
		{
			gameState = new GameState(engine, this);
			gameState->AddRef();

			level = new Level(gameState);
		}

		SceneLevel::~SceneLevel()
		{
			this->DisposeLevel();

			FOREACH(points, SafeRelease(&points[i]);)

			SafeRelease(&level);
			SafeRelease(&gameState);
		}
		#pragma endregion

		#pragma region Member - Init
		void SceneLevel::Initialize(const InitializationArgs& args)
		{
#if TIKI_USE_SCENEGRAPH
			SceneGraph.Initialize(RectangleF::Create(-1024,-1024, 2048, 2048), 10);
#endif

			//Light
			LightObject* lo = new LightObject(engine);
			lo->PRS.SPosition() = Vector3(0, 256, 0);
			lo->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
			lo->GetLight()->SetColor(Color::White);
			lo->GetLight()->SetRange(1000);
			this->AddElement(lo);

			// Camera
			CameraObject* go = new CameraObject(engine);
			(new CameraRTS(go, level->GetTerrain()));

			mainCamera = go->GetCameraComponent();
			this->AddElement(go);

			// PostProcess
			engine->graphics->AddPostProcess(new PPFogOfWar(gameState));
			
			//auto ssao = new PPScreenSpaceAmbientOcclusion(engine);
			//temp = ssao->GetAO();
			//engine->graphics->AddPostProcess(ssao);

			//auto blur = new PPBlur(engine);
			//blur->GetPasses()[0]->SetInput("tex", temp);
			//blur->GetPasses()[1]->SetOutput(0, temp);
			//engine->graphics->AddPostProcess(blur);

			Scene::Initialize(args);
		}
		#pragma endregion

		#pragma region Member - Level
		bool SceneLevel::LoadLevel(Int64 id)
		{
			if (level->GetId() != 0) DisposeLevel();

			const char* tmp = 0;
			sqlite3_stmt* state = 0;

			ostringstream sql;
			sql << "SELECT * FROM \"tiki_level\" WHERE \"ID\" = '" << id << "';";

			int r = sqlite3_prepare(engine->GetDB(), sql.str().c_str(), (Int32)sql.str().size(), &state, &tmp);

			if (r != SQLITE_OK || sqlite3_step(state) != SQLITE_ROW)
			{
				return false;
			}

			level->LoadFromDatabase(state);
			level->AddRef();
			sqlite3_finalize(state);

			//////////////
			// Load Points
			sql = ostringstream();
			sql << "SELECT * FROM \"tiki_level_points\" WHERE \"LevelID\" = '" << id << "';";

			r = sqlite3_prepare(engine->GetDB(), sql.str().c_str(), (Int32)sql.str().size(), &state, &tmp);

			if (r == SQLITE_OK)
			{
				while (sqlite3_step(state) == SQLITE_ROW)
				{
					LevelPoint* point = new LevelPoint(gameState);
					point->LoadFromDatabase(state);

					if (point->GType() == 1)
					{
						mainCamera->GetGameObject()->PRS.SPosition() = Vector3(
							point->GPosition().X,
							32.0f,
							point->GPosition().Y
						);
					}

					points.Add(point);
				}
				sqlite3_finalize(state);
			}

			/////////////////
			// Init GameState
			gameState->LoadLevel(level);

			///////////////
			// Load Objects
			sql = ostringstream();
			sql << "SELECT * FROM \"tiki_level_objects\" WHERE \"LevelID\" = '" << id << "';";

			r = sqlite3_prepare(engine->GetDB(), sql.str().c_str(), (Int32)sql.str().size(), &state, &tmp);

			if (r == SQLITE_OK)
			{
				while (sqlite3_step(state) == SQLITE_ROW)
				{
					LevelObject* object = new LevelObject(gameState);
					object->LoadFromDatabase(state);
				}
				sqlite3_finalize(state);
			}

			return true;
		}

		void SceneLevel::DisposeLevel()
		{
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void SceneLevel::Draw(const DrawArgs& args)
		{
			if (level) level->Draw(args);
			
			Scene::Draw(args);
			gameState->Draw(args);
		}

		void SceneLevel::Update(const UpdateArgs& args)
		{
			if (level) level->Update(args);

			Scene::Update(args);
			gameState->Update(args);
		}
		#pragma endregion
	}
}
