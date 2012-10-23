#pragma once

#include "Core/Scene.h"
#include "Core/sqlite3.h"

#include "Game/Level.h"
#include "Game/LevelEnemy.h"
#include "Game/LevelObject.h"

namespace TikiEngine
{
	namespace Game
	{
		class GameState;

		class SceneLevel : public Scene
		{
			friend class GameState;

		public:

			SceneLevel(Engine* engine);
			~SceneLevel();

			void Initialize(const InitializationArgs& args);

			bool LoadLevel(Int64 id);
			void DisposeLevel();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			Level* GetLevel();
			List<LevelObject*>* GetObjects();
			Camera* GetCamera();

		private:

			Level* level;
			List<LevelEnemy*> enemies;
			List<LevelObject*> objects;
			
			Camera* mainCamera;

			GameState* gameState;

			sqlite3* db;

		};	
	}
}