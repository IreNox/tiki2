
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
#include "Game/PPDepthOfField.h"
#include "Game/PPScreenSpaceAmbientOcclusion.h"

#include "Game/PlayerBase.h"
#include "Game/EnemyBase.h"
#include "Game/TikiBot.h"

using namespace TikiEngine::Objects;
using namespace TikiEngine::Scripts;
using namespace TikiEngine::Graphics;
using namespace TikiEngine::AI;

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		SceneLevel::SceneLevel(Engine* engine)
			: Scene(engine), levelId(0), gameState(0), level(0)
		{
		}

		SceneLevel::~SceneLevel()
		{
			this->DisposeLevel();

			FOREACH_CODE(points, SafeRelease(&points[i]);)

			SafeRelease(&level);
			SafeRelease(&gameState);
		}
		#pragma endregion

		#pragma region Member - Init
		void SceneLevel::Initialize(const InitializationArgs& args)
		{
			SceneGraph.Initialize(RectangleF::Create(-256,-256, 512, 512), 6);

			gameState = TIKI_NEW GameState(engine, this);
			gameState->AddRef();

			level = TIKI_NEW Level(gameState);

			//Light
			LightObject* lo = TIKI_NEW LightObject(engine);
			lo->PRS.SPosition() = Vector3(-256, 256, 64);
			lo->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(-1.59f, -0.92f, 0);
			lo->GetLight()->SetColor(Color::White);
			lo->GetLight()->SetRange(1000);
			this->AddElement(lo);

			// Camera
			CameraObject* go = TIKI_NEW CameraObject(engine);
			(TIKI_NEW CameraRTS(go, level->GetTerrain()));
			this->mainCamera = go->GetCameraComponent();
			this->AddElement(go);

			// PostProcess
			engine->graphics->AddPostProcess(TIKI_NEW PPFogOfWar(gameState));
			
			//auto ssao = TIKI_NEW PPScreenSpaceAmbientOcclusion(engine);
			//temp = ssao->GetAO();
			//engine->graphics->AddPostProcess(ssao);

			//auto dof = TIKI_NEW PPDepthOfField(engine);
			//engine->graphics->AddPostProcess(dof);

			engine->content->LoadModel(L"unit_marine");
			engine->content->LoadModel(L"unit_soldier");

			engine->content->LoadModel(L"tower_enemy");
			engine->content->LoadModel(L"tower_player");

			Scene::Initialize(args);

			if (levelId)
			{
				this->LoadLevel(levelId);
			}
		}
		#pragma endregion

		#pragma region Member - Level
		bool SceneLevel::LoadLevel(Int64 id)
		{
			if (!initialized)
			{
				levelId = id;
				return true;
			}
			levelId = 0;

			if (level->GetId() != 0) DisposeLevel();

			const char* tmp = 0;
			sqlite3_stmt* state = 0;

			string sql = "SELECT * FROM \"tiki_level\" WHERE \"ID\" = '" + StringConvert::ToString(id) + "';";

			int r = sqlite3_prepare(engine->GetDB(), sql.CStr(), (Int32)sql.Length(), &state, &tmp);

			if (r != SQLITE_OK || sqlite3_step(state) != SQLITE_ROW)
			{
				return false;
			}

			level->LoadFromDatabase(state);
			level->AddRef();
			sqlite3_finalize(state);

			//////////////
			// Load Points
			sql = "SELECT * FROM \"tiki_level_points\" WHERE \"LevelID\" = '" + StringConvert::ToString(id) + "';";

			r = sqlite3_prepare(engine->GetDB(), sql.CStr(), (Int32)sql.Length(), &state, &tmp);

			if (r == SQLITE_OK)
			{
				while (sqlite3_step(state) == SQLITE_ROW)
				{
					LevelPoint* point = TIKI_NEW LevelPoint(gameState);
					point->LoadFromDatabase(state);

					if (point->GType() == 1)
					{
						mainCamera->GetGameObject()->PRS.SPosition() = Vector3(
							point->GPosition().X,
							32.0f,
							point->GPosition().Y
						);

						gameState->GetPart<PlayerBase>(0)->SpawnPoint = point;
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
			sql = "SELECT * FROM \"tiki_level_objects\" WHERE \"LevelID\" = '" + StringConvert::ToString(id) + "';";

			r = sqlite3_prepare(engine->GetDB(), sql.CStr(), (Int32)sql.Length(), &state, &tmp);

			if (r == SQLITE_OK)
			{
				while (sqlite3_step(state) == SQLITE_ROW)
				{
					LevelObject* object = TIKI_NEW LevelObject(gameState);
					object->LoadFromDatabase(state);
				}
				sqlite3_finalize(state);
			}

			gameState->InitLevel();
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

#if TIKI_CULLING
			FOREACH_PTR_CALL(drawContent, Draw(args))
#else
			SceneGraph.Draw(args);
#endif
			gameState->Draw(args);
		}

		void SceneLevel::Update(const UpdateArgs& args)
		{
			if (level) level->Update(args);

			SceneGraph.Update(args);
			gameState->Update(args);

#if TIKI_CULLING && TIKI_USE_SCENEGRAPH
			DoFoWCulling();
#else
			hudContent.Clear();
			hudContent.AddRange(SceneGraph.GetAllGameObjects());

			drawContent.Clear();
			drawContent.AddRange(SceneGraph.GetAllGameObjects());
#endif

			SceneGraph.LateUpdate(args);
		}
		#pragma endregion

#pragma region Culling
		void SceneLevel::DoFoWCulling()
		{
#if TIKI_USE_SCENEGRAPH
			hudContent.Clear();
			drawContent.Clear();

			Frustum frustum = mainCamera->GetFrustum();
			SceneGraph.Do([&](GameObject* go)
			{
				TikiBot* bot = go->GetComponent<TikiBot>();
				if(bot)
				{
					if(bot->GetFaction() == 0)
					{
						hudContent.Add(go);
						if(go->GetSceneGraphElement().IsInsideFrustum(frustum))
						{
							drawContent.Add(go);
						}
					}
					else
					{
						if(go->GetSceneGraphElement().IsVisible())
						{
							hudContent.Add(go);
							if(go->GetSceneGraphElement().IsInsideFrustum(frustum))
							{
								drawContent.Add(go);
							}
						}
						else
						{
							go->GetSceneGraphElement().IsCulled = true;
						}
					}
				}
				else
				{
					if(go->GetSceneGraphElement().IsInsideFrustum(frustum))
					{
						drawContent.Add(go);
					}
				}
			});
#endif
		}
#pragma  endregion
	}
}
